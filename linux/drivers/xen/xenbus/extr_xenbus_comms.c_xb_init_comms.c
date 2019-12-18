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
struct xenstore_domain_interface {scalar_t__ req_prod; scalar_t__ req_cons; scalar_t__ rsp_prod; scalar_t__ rsp_cons; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int bind_evtchn_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rebind_evtchn_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_devices ; 
 int /*<<< orphan*/  wake_waiting ; 
 int /*<<< orphan*/  xb_waitq ; 
 int /*<<< orphan*/  xen_store_evtchn ; 
 struct xenstore_domain_interface* xen_store_interface ; 
 int xenbus_irq ; 
 scalar_t__ xenbus_task ; 
 int /*<<< orphan*/  xenbus_thread ; 

int xb_init_comms(void)
{
	struct xenstore_domain_interface *intf = xen_store_interface;

	if (intf->req_prod != intf->req_cons)
		pr_err("request ring is not quiescent (%08x:%08x)!\n",
		       intf->req_cons, intf->req_prod);

	if (intf->rsp_prod != intf->rsp_cons) {
		pr_warn("response ring is not quiescent (%08x:%08x): fixing up\n",
			intf->rsp_cons, intf->rsp_prod);
		/* breaks kdump */
		if (!reset_devices)
			intf->rsp_cons = intf->rsp_prod;
	}

	if (xenbus_irq) {
		/* Already have an irq; assume we're resuming */
		rebind_evtchn_irq(xen_store_evtchn, xenbus_irq);
	} else {
		int err;

		err = bind_evtchn_to_irqhandler(xen_store_evtchn, wake_waiting,
						0, "xenbus", &xb_waitq);
		if (err < 0) {
			pr_err("request irq failed %i\n", err);
			return err;
		}

		xenbus_irq = err;

		if (!xenbus_task) {
			xenbus_task = kthread_run(xenbus_thread, NULL,
						  "xenbus");
			if (IS_ERR(xenbus_task))
				return PTR_ERR(xenbus_task);
		}
	}

	return 0;
}