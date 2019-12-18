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
struct xvcu_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  vcu_slcr_ba; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VCU_PLL_CTRL ; 
 int /*<<< orphan*/  VCU_PLL_CTRL_BYPASS_MASK ; 
 int /*<<< orphan*/  VCU_PLL_CTRL_BYPASS_SHIFT ; 
 int /*<<< orphan*/  VCU_PLL_CTRL_RESET_MASK ; 
 int /*<<< orphan*/  VCU_PLL_CTRL_RESET_SHIFT ; 
 int /*<<< orphan*/  VCU_PLL_STATUS ; 
 int VCU_PLL_STATUS_LOCK_STATUS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int xvcu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xvcu_set_vcu_pll_info (struct xvcu_device*) ; 
 int /*<<< orphan*/  xvcu_write_field_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xvcu_set_pll(struct xvcu_device *xvcu)
{
	u32 lock_status;
	unsigned long timeout;
	int ret;

	ret = xvcu_set_vcu_pll_info(xvcu);
	if (ret) {
		dev_err(xvcu->dev, "failed to set pll info\n");
		return ret;
	}

	xvcu_write_field_reg(xvcu->vcu_slcr_ba, VCU_PLL_CTRL,
			     1, VCU_PLL_CTRL_BYPASS_MASK,
			     VCU_PLL_CTRL_BYPASS_SHIFT);
	xvcu_write_field_reg(xvcu->vcu_slcr_ba, VCU_PLL_CTRL,
			     1, VCU_PLL_CTRL_RESET_MASK,
			     VCU_PLL_CTRL_RESET_SHIFT);
	xvcu_write_field_reg(xvcu->vcu_slcr_ba, VCU_PLL_CTRL,
			     0, VCU_PLL_CTRL_RESET_MASK,
			     VCU_PLL_CTRL_RESET_SHIFT);
	/*
	 * Defined the timeout for the max time to wait the
	 * PLL_STATUS to be locked.
	 */
	timeout = jiffies + msecs_to_jiffies(2000);
	do {
		lock_status = xvcu_read(xvcu->vcu_slcr_ba, VCU_PLL_STATUS);
		if (lock_status & VCU_PLL_STATUS_LOCK_STATUS_MASK) {
			xvcu_write_field_reg(xvcu->vcu_slcr_ba, VCU_PLL_CTRL,
					     0, VCU_PLL_CTRL_BYPASS_MASK,
					     VCU_PLL_CTRL_BYPASS_SHIFT);
			return 0;
		}
	} while (!time_after(jiffies, timeout));

	/* PLL is not locked even after the timeout of the 2sec */
	dev_err(xvcu->dev, "PLL is not locked\n");
	return -ETIMEDOUT;
}