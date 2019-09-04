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
 int /*<<< orphan*/  SEC_RESET_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mei_txe_hw_is_ready (struct mei_device*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_txe_readiness_wait(struct mei_device *dev)
{
	if (mei_txe_hw_is_ready(dev))
		return 0;

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_hw_ready, dev->recvd_hw_ready,
			msecs_to_jiffies(SEC_RESET_WAIT_TIMEOUT));
	mutex_lock(&dev->device_lock);
	if (!dev->recvd_hw_ready) {
		dev_err(dev->dev, "wait for readiness failed\n");
		return -ETIME;
	}

	dev->recvd_hw_ready = false;
	return 0;
}