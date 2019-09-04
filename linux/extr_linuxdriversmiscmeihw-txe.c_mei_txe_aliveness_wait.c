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
typedef  scalar_t__ u32 ;
struct mei_txe_hw {scalar_t__ aliveness; int /*<<< orphan*/  wait_aliveness_resp; } ;
struct mei_device {int /*<<< orphan*/  pg_event; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  MEI_PG_EVENT_IDLE ; 
 int /*<<< orphan*/  MEI_PG_EVENT_RECEIVED ; 
 int /*<<< orphan*/  SEC_ALIVENESS_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,long,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long const) ; 
 void* mei_txe_aliveness_get (struct mei_device*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long const) ; 

__attribute__((used)) static int mei_txe_aliveness_wait(struct mei_device *dev, u32 expected)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);
	const unsigned long timeout =
			msecs_to_jiffies(SEC_ALIVENESS_WAIT_TIMEOUT);
	long err;
	int ret;

	hw->aliveness = mei_txe_aliveness_get(dev);
	if (hw->aliveness == expected)
		return 0;

	mutex_unlock(&dev->device_lock);
	err = wait_event_timeout(hw->wait_aliveness_resp,
			dev->pg_event == MEI_PG_EVENT_RECEIVED, timeout);
	mutex_lock(&dev->device_lock);

	hw->aliveness = mei_txe_aliveness_get(dev);
	ret = hw->aliveness == expected ? 0 : -ETIME;

	if (ret)
		dev_warn(dev->dev, "aliveness timed out = %ld aliveness = %d event = %d\n",
			err, hw->aliveness, dev->pg_event);
	else
		dev_dbg(dev->dev, "aliveness settled after = %d msec aliveness = %d event = %d\n",
			jiffies_to_msecs(timeout - err),
			hw->aliveness, dev->pg_event);

	dev->pg_event = MEI_PG_EVENT_IDLE;
	return ret;
}