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
struct device {int dummy; } ;
struct rproc {int name; int /*<<< orphan*/  lock; int /*<<< orphan*/  firmware; struct device dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  rproc_coredump (struct rproc*) ; 
 int rproc_start (struct rproc*,struct firmware const*) ; 
 int rproc_stop (struct rproc*,int) ; 

int rproc_trigger_recovery(struct rproc *rproc)
{
	const struct firmware *firmware_p;
	struct device *dev = &rproc->dev;
	int ret;

	dev_err(dev, "recovering %s\n", rproc->name);

	ret = mutex_lock_interruptible(&rproc->lock);
	if (ret)
		return ret;

	ret = rproc_stop(rproc, true);
	if (ret)
		goto unlock_mutex;

	/* generate coredump */
	rproc_coredump(rproc);

	/* load firmware */
	ret = request_firmware(&firmware_p, rproc->firmware, dev);
	if (ret < 0) {
		dev_err(dev, "request_firmware failed: %d\n", ret);
		goto unlock_mutex;
	}

	/* boot the remote processor up again */
	ret = rproc_start(rproc, firmware_p);

	release_firmware(firmware_p);

unlock_mutex:
	mutex_unlock(&rproc->lock);
	return ret;
}