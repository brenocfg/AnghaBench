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
struct mei_device {scalar_t__ pg_event; int /*<<< orphan*/  wait_pg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ MEI_PG_EVENT_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_WAIT ; 
 scalar_t__ MEI_PG_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mei_pg_state (struct mei_device*) ; 
 int /*<<< orphan*/  mei_pg_state_str (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mei_hbm_pg_enter_res(struct mei_device *dev)
{
	if (mei_pg_state(dev) != MEI_PG_OFF ||
	    dev->pg_event != MEI_PG_EVENT_WAIT) {
		dev_err(dev->dev, "hbm: pg entry response: state mismatch [%s, %d]\n",
			mei_pg_state_str(mei_pg_state(dev)), dev->pg_event);
		return -EPROTO;
	}

	dev->pg_event = MEI_PG_EVENT_RECEIVED;
	wake_up(&dev->wait_pg);

	return 0;
}