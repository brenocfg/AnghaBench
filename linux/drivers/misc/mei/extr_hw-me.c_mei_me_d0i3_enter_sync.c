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
typedef  int u32 ;
struct mei_me_hw {int /*<<< orphan*/  pg_state; } ;
struct mei_device {scalar_t__ pg_event; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_pg; } ;

/* Variables and functions */
 int ETIME ; 
 int H_D0I3C_CIP ; 
 int H_D0I3C_I3 ; 
 int /*<<< orphan*/  MEI_D0I3_TIMEOUT ; 
 int /*<<< orphan*/  MEI_PGI_TIMEOUT ; 
 scalar_t__ MEI_PG_EVENT_IDLE ; 
 scalar_t__ MEI_PG_EVENT_INTR_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_INTR_WAIT ; 
 scalar_t__ MEI_PG_EVENT_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_WAIT ; 
 int /*<<< orphan*/  MEI_PG_ISOLATION_ENTRY_REQ_CMD ; 
 int /*<<< orphan*/  MEI_PG_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int mei_hbm_pg (struct mei_device*,int /*<<< orphan*/ ) ; 
 int mei_me_d0i3_set (struct mei_device*,int) ; 
 int mei_me_d0i3c_read (struct mei_device*) ; 
 unsigned long mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int mei_me_d0i3_enter_sync(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);
	unsigned long d0i3_timeout = mei_secs_to_jiffies(MEI_D0I3_TIMEOUT);
	unsigned long pgi_timeout = mei_secs_to_jiffies(MEI_PGI_TIMEOUT);
	int ret;
	u32 reg;

	reg = mei_me_d0i3c_read(dev);
	if (reg & H_D0I3C_I3) {
		/* we are in d0i3, nothing to do */
		dev_dbg(dev->dev, "d0i3 set not needed\n");
		ret = 0;
		goto on;
	}

	/* PGI entry procedure */
	dev->pg_event = MEI_PG_EVENT_WAIT;

	ret = mei_hbm_pg(dev, MEI_PG_ISOLATION_ENTRY_REQ_CMD);
	if (ret)
		/* FIXME: should we reset here? */
		goto out;

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_RECEIVED, pgi_timeout);
	mutex_lock(&dev->device_lock);

	if (dev->pg_event != MEI_PG_EVENT_RECEIVED) {
		ret = -ETIME;
		goto out;
	}
	/* end PGI entry procedure */

	dev->pg_event = MEI_PG_EVENT_INTR_WAIT;

	reg = mei_me_d0i3_set(dev, true);
	if (!(reg & H_D0I3C_CIP)) {
		dev_dbg(dev->dev, "d0i3 enter wait not needed\n");
		ret = 0;
		goto on;
	}

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED, d0i3_timeout);
	mutex_lock(&dev->device_lock);

	if (dev->pg_event != MEI_PG_EVENT_INTR_RECEIVED) {
		reg = mei_me_d0i3c_read(dev);
		if (!(reg & H_D0I3C_I3)) {
			ret = -ETIME;
			goto out;
		}
	}

	ret = 0;
on:
	hw->pg_state = MEI_PG_ON;
out:
	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_dbg(dev->dev, "d0i3 enter ret = %d\n", ret);
	return ret;
}