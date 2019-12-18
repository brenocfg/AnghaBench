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
struct mei_device {int dummy; } ;
struct mei_cl {int notify_ev; scalar_t__ ev_async; int /*<<< orphan*/  ev_wait; int /*<<< orphan*/  notify_en; struct mei_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_PRI ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  kill_fasync (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cl_bus_notify_event (struct mei_cl*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void mei_cl_notify(struct mei_cl *cl)
{
	struct mei_device *dev;

	if (!cl || !cl->dev)
		return;

	dev = cl->dev;

	if (!cl->notify_en)
		return;

	cl_dbg(dev, cl, "notify event");
	cl->notify_ev = true;
	if (!mei_cl_bus_notify_event(cl))
		wake_up_interruptible(&cl->ev_wait);

	if (cl->ev_async)
		kill_fasync(&cl->ev_async, SIGIO, POLL_PRI);

}