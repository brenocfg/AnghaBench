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
struct mei_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pg_event; } ;

/* Variables and functions */
 int H_D0I3C_I3 ; 
 int /*<<< orphan*/  MEI_PG_EVENT_IDLE ; 
 int /*<<< orphan*/  MEI_PG_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_me_d0i3_set (struct mei_device*,int) ; 
 int mei_me_d0i3c_read (struct mei_device*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_me_d0i3_enter(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);
	u32 reg;

	reg = mei_me_d0i3c_read(dev);
	if (reg & H_D0I3C_I3) {
		/* we are in d0i3, nothing to do */
		dev_dbg(dev->dev, "already d0i3 : set not needed\n");
		goto on;
	}

	mei_me_d0i3_set(dev, false);
on:
	hw->pg_state = MEI_PG_ON;
	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_dbg(dev->dev, "d0i3 enter\n");
	return 0;
}