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
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  dev; scalar_t__ reset_count; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MEI_DEV_DISABLED ; 
 scalar_t__ MEI_DEV_INITIALIZING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mei_clear_interrupts (struct mei_device*) ; 
 scalar_t__ mei_hbm_start_wait (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_version_is_supported (struct mei_device*) ; 
 int /*<<< orphan*/  mei_host_is_ready (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hw_config (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hw_is_ready (struct mei_device*) ; 
 int mei_reset (struct mei_device*) ; 
 int /*<<< orphan*/  mei_set_devstate (struct mei_device*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mei_start(struct mei_device *dev)
{
	int ret;

	mutex_lock(&dev->device_lock);

	/* acknowledge interrupt and stop interrupts */
	mei_clear_interrupts(dev);

	mei_hw_config(dev);

	dev_dbg(dev->dev, "reset in start the mei device.\n");

	dev->reset_count = 0;
	do {
		mei_set_devstate(dev, MEI_DEV_INITIALIZING);
		ret = mei_reset(dev);

		if (ret == -ENODEV || dev->dev_state == MEI_DEV_DISABLED) {
			dev_err(dev->dev, "reset failed ret = %d", ret);
			goto err;
		}
	} while (ret);

	if (mei_hbm_start_wait(dev)) {
		dev_err(dev->dev, "HBM haven't started");
		goto err;
	}

	if (!mei_host_is_ready(dev)) {
		dev_err(dev->dev, "host is not ready.\n");
		goto err;
	}

	if (!mei_hw_is_ready(dev)) {
		dev_err(dev->dev, "ME is not ready.\n");
		goto err;
	}

	if (!mei_hbm_version_is_supported(dev)) {
		dev_dbg(dev->dev, "MEI start failed.\n");
		goto err;
	}

	dev_dbg(dev->dev, "link layer has been established.\n");

	mutex_unlock(&dev->device_lock);
	return 0;
err:
	dev_err(dev->dev, "link layer initialization failed.\n");
	mei_set_devstate(dev, MEI_DEV_DISABLED);
	mutex_unlock(&dev->device_lock);
	return -ENODEV;
}