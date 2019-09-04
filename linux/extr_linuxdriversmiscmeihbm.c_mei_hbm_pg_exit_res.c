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
struct mei_device {int pg_event; int /*<<< orphan*/  wait_pg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROTO ; 
#define  MEI_PG_EVENT_IDLE 129 
 void* MEI_PG_EVENT_RECEIVED ; 
#define  MEI_PG_EVENT_WAIT 128 
 scalar_t__ MEI_PG_ON ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mei_hbm_pg_resume (struct mei_device*) ; 
 scalar_t__ mei_pg_state (struct mei_device*) ; 
 int /*<<< orphan*/  mei_pg_state_str (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mei_hbm_pg_exit_res(struct mei_device *dev)
{
	if (mei_pg_state(dev) != MEI_PG_ON ||
	    (dev->pg_event != MEI_PG_EVENT_WAIT &&
	     dev->pg_event != MEI_PG_EVENT_IDLE)) {
		dev_err(dev->dev, "hbm: pg exit response: state mismatch [%s, %d]\n",
			mei_pg_state_str(mei_pg_state(dev)), dev->pg_event);
		return -EPROTO;
	}

	switch (dev->pg_event) {
	case MEI_PG_EVENT_WAIT:
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		wake_up(&dev->wait_pg);
		break;
	case MEI_PG_EVENT_IDLE:
		/*
		* If the driver is not waiting on this then
		* this is HW initiated exit from PG.
		* Start runtime pm resume sequence to exit from PG.
		*/
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		mei_hbm_pg_resume(dev);
		break;
	default:
		WARN(1, "hbm: pg exit response: unexpected pg event = %d\n",
		     dev->pg_event);
		return -EPROTO;
	}

	return 0;
}