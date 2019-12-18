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
struct mei_device {int recvd_hw_ready; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_hw_ready; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  MEI_HW_READY_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_me_hw_reset_release (struct mei_device*) ; 
 int /*<<< orphan*/  mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_me_hw_ready_wait(struct mei_device *dev)
{
	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_hw_ready,
			dev->recvd_hw_ready,
			mei_secs_to_jiffies(MEI_HW_READY_TIMEOUT));
	mutex_lock(&dev->device_lock);
	if (!dev->recvd_hw_ready) {
		dev_err(dev->dev, "wait hw ready failed\n");
		return -ETIME;
	}

	mei_me_hw_reset_release(dev);
	dev->recvd_hw_ready = false;
	return 0;
}