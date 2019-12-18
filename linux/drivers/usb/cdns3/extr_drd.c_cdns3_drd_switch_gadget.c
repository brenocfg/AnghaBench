#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cdns3 {TYPE_1__* otg_regs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  cmd; int /*<<< orphan*/  sts; } ;

/* Variables and functions */
 int OTGCMD_DEV_BUS_DROP ; 
 int OTGCMD_DEV_BUS_REQ ; 
 int OTGCMD_DEV_POWER_OFF ; 
 int OTGCMD_HOST_BUS_DROP ; 
 int OTGCMD_HOST_POWER_OFF ; 
 int OTGCMD_OTG_DIS ; 
 int OTGSTATE_DEV_STATE_MASK ; 
 int OTGSTS_DEV_READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_poll_timeout_atomic (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int cdns3_drd_switch_gadget(struct cdns3 *cdns, int on)
{
	int ret, val;
	u32 reg = OTGCMD_OTG_DIS;

	/* switch OTG core */
	if (on) {
		writel(OTGCMD_DEV_BUS_REQ | reg, &cdns->otg_regs->cmd);

		dev_dbg(cdns->dev, "Waiting till Device mode is turned on\n");

		ret = readl_poll_timeout_atomic(&cdns->otg_regs->sts, val,
						val & OTGSTS_DEV_READY,
						1, 100000);
		if (ret) {
			dev_err(cdns->dev, "timeout waiting for dev_ready\n");
			return ret;
		}
	} else {
		/*
		 * driver should wait at least 10us after disabling Device
		 * before turning-off Device (DEV_BUS_DROP)
		 */
		usleep_range(20, 30);
		writel(OTGCMD_HOST_BUS_DROP | OTGCMD_DEV_BUS_DROP |
		       OTGCMD_DEV_POWER_OFF | OTGCMD_HOST_POWER_OFF,
		       &cdns->otg_regs->cmd);
		/* Waiting till DEV_IDLE state.*/
		readl_poll_timeout_atomic(&cdns->otg_regs->state, val,
					  !(val & OTGSTATE_DEV_STATE_MASK),
					  1, 2000000);
	}

	return 0;
}