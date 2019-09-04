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
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  dev; } ;
struct mei_cl {struct mei_device* dev; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENODEV ; 
 scalar_t__ MEI_DEV_POWER_DOWN ; 
 scalar_t__ WARN_ON (int) ; 
 int __mei_cl_disconnect (struct mei_cl*) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  cl_err (struct mei_device*,struct mei_cl*,char*,int) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 scalar_t__ mei_cl_is_fixed_address (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_set_disconnected (struct mei_cl*) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

int mei_cl_disconnect(struct mei_cl *cl)
{
	struct mei_device *dev;
	int rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	cl_dbg(dev, cl, "disconnecting");

	if (!mei_cl_is_connected(cl))
		return 0;

	if (mei_cl_is_fixed_address(cl)) {
		mei_cl_set_disconnected(cl);
		return 0;
	}

	if (dev->dev_state == MEI_DEV_POWER_DOWN) {
		cl_dbg(dev, cl, "Device is powering down, don't bother with disconnection\n");
		mei_cl_set_disconnected(cl);
		return 0;
	}

	rets = pm_runtime_get(dev->dev);
	if (rets < 0 && rets != -EINPROGRESS) {
		pm_runtime_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		return rets;
	}

	rets = __mei_cl_disconnect(cl);

	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);

	return rets;
}