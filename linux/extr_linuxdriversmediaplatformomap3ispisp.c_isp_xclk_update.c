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
struct isp_xclk {int id; int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPTCTRL_CTRL_DIVA_MASK ; 
 int ISPTCTRL_CTRL_DIVA_SHIFT ; 
 int /*<<< orphan*/  ISPTCTRL_CTRL_DIVB_MASK ; 
 int ISPTCTRL_CTRL_DIVB_SHIFT ; 
 int /*<<< orphan*/  ISP_TCTRL_CTRL ; 
#define  ISP_XCLK_A 129 
#define  ISP_XCLK_B 128 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_MAIN ; 
 int /*<<< orphan*/  isp_reg_clr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp_xclk_update(struct isp_xclk *xclk, u32 divider)
{
	switch (xclk->id) {
	case ISP_XCLK_A:
		isp_reg_clr_set(xclk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTRL_CTRL,
				ISPTCTRL_CTRL_DIVA_MASK,
				divider << ISPTCTRL_CTRL_DIVA_SHIFT);
		break;
	case ISP_XCLK_B:
		isp_reg_clr_set(xclk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTRL_CTRL,
				ISPTCTRL_CTRL_DIVB_MASK,
				divider << ISPTCTRL_CTRL_DIVB_SHIFT);
		break;
	}
}