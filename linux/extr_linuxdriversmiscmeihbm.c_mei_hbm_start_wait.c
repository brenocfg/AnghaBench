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
struct mei_device {scalar_t__ hbm_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_hbm_start; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ MEI_HBM_IDLE ; 
 scalar_t__ MEI_HBM_STARTING ; 
 int /*<<< orphan*/  MEI_HBM_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mei_hbm_start_wait(struct mei_device *dev)
{
	int ret;

	if (dev->hbm_state > MEI_HBM_STARTING)
		return 0;

	mutex_unlock(&dev->device_lock);
	ret = wait_event_timeout(dev->wait_hbm_start,
			dev->hbm_state != MEI_HBM_STARTING,
			mei_secs_to_jiffies(MEI_HBM_TIMEOUT));
	mutex_lock(&dev->device_lock);

	if (ret == 0 && (dev->hbm_state <= MEI_HBM_STARTING)) {
		dev->hbm_state = MEI_HBM_IDLE;
		dev_err(dev->dev, "waiting for mei start failed\n");
		return -ETIME;
	}
	return 0;
}