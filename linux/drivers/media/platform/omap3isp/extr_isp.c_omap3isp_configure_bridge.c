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
typedef  unsigned int u32 ;
struct isp_parallel_cfg {unsigned int clk_pol; unsigned int data_lane_shift; } ;
struct isp_device {int dummy; } ;
typedef  enum ccdc_input_entity { ____Placeholder_ccdc_input_entity } ccdc_input_entity ;

/* Variables and functions */
#define  CCDC_INPUT_CCP2B 131 
#define  CCDC_INPUT_CSI2A 130 
#define  CCDC_INPUT_CSI2C 129 
#define  CCDC_INPUT_PARALLEL 128 
 unsigned int ISPCTRL_PAR_BRIDGE_MASK ; 
 unsigned int ISPCTRL_PAR_CLK_POL_INV ; 
 unsigned int ISPCTRL_PAR_CLK_POL_SHIFT ; 
 unsigned int ISPCTRL_PAR_SER_CLK_SEL_CSIA ; 
 unsigned int ISPCTRL_PAR_SER_CLK_SEL_CSIB ; 
 unsigned int ISPCTRL_PAR_SER_CLK_SEL_CSIC ; 
 unsigned int ISPCTRL_PAR_SER_CLK_SEL_MASK ; 
 unsigned int ISPCTRL_PAR_SER_CLK_SEL_PARALLEL ; 
 unsigned int ISPCTRL_SHIFT_MASK ; 
 unsigned int ISPCTRL_SHIFT_SHIFT ; 
 int /*<<< orphan*/  ISP_CTRL ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_MAIN ; 
 unsigned int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3isp_configure_bridge(struct isp_device *isp,
			       enum ccdc_input_entity input,
			       const struct isp_parallel_cfg *parcfg,
			       unsigned int shift, unsigned int bridge)
{
	u32 ispctrl_val;

	ispctrl_val  = isp_reg_readl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
	ispctrl_val &= ~ISPCTRL_SHIFT_MASK;
	ispctrl_val &= ~ISPCTRL_PAR_CLK_POL_INV;
	ispctrl_val &= ~ISPCTRL_PAR_SER_CLK_SEL_MASK;
	ispctrl_val &= ~ISPCTRL_PAR_BRIDGE_MASK;
	ispctrl_val |= bridge;

	switch (input) {
	case CCDC_INPUT_PARALLEL:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_PARALLEL;
		ispctrl_val |= parcfg->clk_pol << ISPCTRL_PAR_CLK_POL_SHIFT;
		shift += parcfg->data_lane_shift;
		break;

	case CCDC_INPUT_CSI2A:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIA;
		break;

	case CCDC_INPUT_CCP2B:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIB;
		break;

	case CCDC_INPUT_CSI2C:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIC;
		break;

	default:
		return;
	}

	ispctrl_val |= ((shift/2) << ISPCTRL_SHIFT_SHIFT) & ISPCTRL_SHIFT_MASK;

	isp_reg_writel(isp, ispctrl_val, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
}