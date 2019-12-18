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
struct pxp_dev {scalar_t__ mmio; } ;

/* Variables and functions */
 int BM_PXP_CTRL_CLKGATE ; 
 int BM_PXP_CTRL_SFTRST ; 
 scalar_t__ HW_PXP_CTRL ; 
 scalar_t__ HW_PXP_CTRL_CLR ; 
 scalar_t__ HW_PXP_CTRL_SET ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pxp_soft_reset(struct pxp_dev *dev)
{
	int ret;
	u32 val;

	writel(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_CLR);
	writel(BM_PXP_CTRL_CLKGATE, dev->mmio + HW_PXP_CTRL_CLR);

	writel(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_SET);

	ret = readl_poll_timeout(dev->mmio + HW_PXP_CTRL, val,
				 val & BM_PXP_CTRL_CLKGATE, 0, 100);
	if (ret < 0)
		return ret;

	writel(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_CLR);
	writel(BM_PXP_CTRL_CLKGATE, dev->mmio + HW_PXP_CTRL_CLR);

	return 0;
}