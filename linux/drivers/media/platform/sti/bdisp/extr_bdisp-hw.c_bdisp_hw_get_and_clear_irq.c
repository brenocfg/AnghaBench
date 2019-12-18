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
struct bdisp_dev {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BLT_ITM0 ; 
 scalar_t__ BLT_ITS ; 
 int BLT_ITS_AQ1_LNA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int bdisp_hw_get_and_clear_irq(struct bdisp_dev *bdisp)
{
	u32 its;

	its = readl(bdisp->regs + BLT_ITS);

	/* Check for the only expected IT: LastNode of AQ1 */
	if (!(its & BLT_ITS_AQ1_LNA)) {
		dev_dbg(bdisp->dev, "Unexpected IT status: 0x%08X\n", its);
		writel(its, bdisp->regs + BLT_ITS);
		return -1;
	}

	/* Clear and mask */
	writel(its, bdisp->regs + BLT_ITS);
	writel(0, bdisp->regs + BLT_ITM0);

	return 0;
}