#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct evtchn_alloc_unbound {scalar_t__ port; int /*<<< orphan*/  remote_dom; int /*<<< orphan*/  dom; } ;
typedef  int /*<<< orphan*/  domid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int EEXIST ; 
 int /*<<< orphan*/  EVTCHNOP_alloc_unbound ; 
 int /*<<< orphan*/  GNTTAB_RESERVED_XENSTORE ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_alloc_unbound*) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_gfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_deinit_comms () ; 
 scalar_t__ xen_store_evtchn ; 
 int /*<<< orphan*/  xen_store_interface ; 
 scalar_t__ xenstored_ready ; 
 int /*<<< orphan*/  xs_resume () ; 
 int /*<<< orphan*/  xs_suspend () ; 
 int /*<<< orphan*/  xs_suspend_cancel () ; 

__attribute__((used)) static long xenbus_alloc(domid_t domid)
{
	struct evtchn_alloc_unbound arg;
	int err = -EEXIST;

	xs_suspend();

	/* If xenstored_ready is nonzero, that means we have already talked to
	 * xenstore and set up watches. These watches will be restored by
	 * xs_resume, but that requires communication over the port established
	 * below that is not visible to anyone until the ioctl returns.
	 *
	 * This can be resolved by splitting the ioctl into two parts
	 * (postponing the resume until xenstored is active) but this is
	 * unnecessarily complex for the intended use where xenstored is only
	 * started once - so return -EEXIST if it's already running.
	 */
	if (xenstored_ready)
		goto out_err;

	gnttab_grant_foreign_access_ref(GNTTAB_RESERVED_XENSTORE, domid,
			virt_to_gfn(xen_store_interface), 0 /* writable */);

	arg.dom = DOMID_SELF;
	arg.remote_dom = domid;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound, &arg);
	if (err)
		goto out_err;

	if (xen_store_evtchn > 0)
		xb_deinit_comms();

	xen_store_evtchn = arg.port;

	xs_resume();

	return arg.port;

 out_err:
	xs_suspend_cancel();
	return err;
}