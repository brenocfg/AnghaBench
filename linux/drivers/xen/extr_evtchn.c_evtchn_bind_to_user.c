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
struct user_evtchn {int port; int enabled; struct per_user_data* user; } ;
struct per_user_data {int /*<<< orphan*/  name; } ;
struct evtchn_close {int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVTCHNOP_close ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_close*) ; 
 int add_evtchn (struct per_user_data*,struct user_evtchn*) ; 
 int bind_evtchn_to_irqhandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct user_evtchn*) ; 
 int /*<<< orphan*/  del_evtchn (struct per_user_data*,struct user_evtchn*) ; 
 int /*<<< orphan*/  evtchn_interrupt ; 
 int evtchn_make_refcounted (int) ; 
 int evtchn_resize_ring (struct per_user_data*) ; 
 struct user_evtchn* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evtchn_bind_to_user(struct per_user_data *u, int port)
{
	struct user_evtchn *evtchn;
	struct evtchn_close close;
	int rc = 0;

	/*
	 * Ports are never reused, so every caller should pass in a
	 * unique port.
	 *
	 * (Locking not necessary because we haven't registered the
	 * interrupt handler yet, and our caller has already
	 * serialized bind operations.)
	 */

	evtchn = kzalloc(sizeof(*evtchn), GFP_KERNEL);
	if (!evtchn)
		return -ENOMEM;

	evtchn->user = u;
	evtchn->port = port;
	evtchn->enabled = true; /* start enabled */

	rc = add_evtchn(u, evtchn);
	if (rc < 0)
		goto err;

	rc = evtchn_resize_ring(u);
	if (rc < 0)
		goto err;

	rc = bind_evtchn_to_irqhandler(port, evtchn_interrupt, 0,
				       u->name, evtchn);
	if (rc < 0)
		goto err;

	rc = evtchn_make_refcounted(port);
	return rc;

err:
	/* bind failed, should close the port now */
	close.port = port;
	if (HYPERVISOR_event_channel_op(EVTCHNOP_close, &close) != 0)
		BUG();
	del_evtchn(u, evtchn);
	return rc;
}