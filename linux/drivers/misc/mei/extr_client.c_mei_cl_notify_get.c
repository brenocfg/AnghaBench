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
struct mei_device {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  hbm_f_ev_supported; } ;
struct mei_cl {int notify_ev; int /*<<< orphan*/  ev_wait; struct mei_device* dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int mei_cl_notify_get(struct mei_cl *cl, bool block, bool *notify_ev)
{
	struct mei_device *dev;
	int rets;

	*notify_ev = false;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	if (!dev->hbm_f_ev_supported) {
		cl_dbg(dev, cl, "notifications not supported\n");
		return -EOPNOTSUPP;
	}

	if (!mei_cl_is_connected(cl))
		return -ENODEV;

	if (cl->notify_ev)
		goto out;

	if (!block)
		return -EAGAIN;

	mutex_unlock(&dev->device_lock);
	rets = wait_event_interruptible(cl->ev_wait, cl->notify_ev);
	mutex_lock(&dev->device_lock);

	if (rets < 0)
		return rets;

out:
	*notify_ev = cl->notify_ev;
	cl->notify_ev = false;
	return 0;
}