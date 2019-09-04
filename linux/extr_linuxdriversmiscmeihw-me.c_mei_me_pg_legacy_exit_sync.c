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
struct mei_me_hw {int /*<<< orphan*/  pg_state; } ;
struct mei_device {scalar_t__ pg_event; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_pg; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  MEI_PGI_TIMEOUT ; 
 scalar_t__ MEI_PG_EVENT_IDLE ; 
 scalar_t__ MEI_PG_EVENT_INTR_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_INTR_WAIT ; 
 scalar_t__ MEI_PG_EVENT_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_WAIT ; 
 int /*<<< orphan*/  MEI_PG_ISOLATION_EXIT_RES_CMD ; 
 int /*<<< orphan*/  MEI_PG_OFF ; 
 int mei_hbm_pg (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_pg_unset (struct mei_device*) ; 
 unsigned long mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int mei_me_pg_legacy_exit_sync(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);
	unsigned long timeout = mei_secs_to_jiffies(MEI_PGI_TIMEOUT);
	int ret;

	if (dev->pg_event == MEI_PG_EVENT_RECEIVED)
		goto reply;

	dev->pg_event = MEI_PG_EVENT_WAIT;

	mei_me_pg_unset(dev);

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_RECEIVED, timeout);
	mutex_lock(&dev->device_lock);

reply:
	if (dev->pg_event != MEI_PG_EVENT_RECEIVED) {
		ret = -ETIME;
		goto out;
	}

	dev->pg_event = MEI_PG_EVENT_INTR_WAIT;
	ret = mei_hbm_pg(dev, MEI_PG_ISOLATION_EXIT_RES_CMD);
	if (ret)
		return ret;

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED, timeout);
	mutex_lock(&dev->device_lock);

	if (dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED)
		ret = 0;
	else
		ret = -ETIME;

out:
	dev->pg_event = MEI_PG_EVENT_IDLE;
	hw->pg_state = MEI_PG_OFF;

	return ret;
}