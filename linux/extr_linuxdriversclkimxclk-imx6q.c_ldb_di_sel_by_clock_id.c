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

/* Variables and functions */
 int ENOENT ; 
#define  IMX6QDL_CLK_MMDC_CH1_AXI 132 
#define  IMX6QDL_CLK_PLL2_PFD0_352M 131 
#define  IMX6QDL_CLK_PLL2_PFD2_396M 130 
#define  IMX6QDL_CLK_PLL3_USB_OTG 129 
#define  IMX6QDL_CLK_PLL5_VIDEO_DIV 128 
 int /*<<< orphan*/  IMX_CHIP_REVISION_1_0 ; 
 int /*<<< orphan*/  clk_on_imx6q () ; 
 int /*<<< orphan*/  imx_get_soc_revision () ; 

__attribute__((used)) static int ldb_di_sel_by_clock_id(int clock_id)
{
	switch (clock_id) {
	case IMX6QDL_CLK_PLL5_VIDEO_DIV:
		if (clk_on_imx6q() &&
		    imx_get_soc_revision() == IMX_CHIP_REVISION_1_0)
			return -ENOENT;
		return 0;
	case IMX6QDL_CLK_PLL2_PFD0_352M:
		return 1;
	case IMX6QDL_CLK_PLL2_PFD2_396M:
		return 2;
	case IMX6QDL_CLK_MMDC_CH1_AXI:
		return 3;
	case IMX6QDL_CLK_PLL3_USB_OTG:
		return 4;
	default:
		return -ENOENT;
	}
}