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
struct omap3isp_ccdc_lsc_config {int offset; int gain_mode_n; int gain_mode_m; int gain_format; int initial_x; int initial_y; } ;
struct isp_device {int dummy; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_LSC_CONFIG ; 
 int ISPCCDC_LSC_GAIN_FORMAT_SHIFT ; 
 int ISPCCDC_LSC_GAIN_MODE_M_SHIFT ; 
 int ISPCCDC_LSC_GAIN_MODE_N_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_LSC_INITIAL ; 
 int ISPCCDC_LSC_INITIAL_X_MASK ; 
 int ISPCCDC_LSC_INITIAL_X_SHIFT ; 
 int ISPCCDC_LSC_INITIAL_Y_MASK ; 
 int ISPCCDC_LSC_INITIAL_Y_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_LSC_TABLE_OFFSET ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_lsc_setup_regs(struct isp_ccdc_device *ccdc,
				struct omap3isp_ccdc_lsc_config *cfg)
{
	struct isp_device *isp = to_isp_device(ccdc);
	int reg;

	isp_reg_writel(isp, cfg->offset, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_LSC_TABLE_OFFSET);

	reg = 0;
	reg |= cfg->gain_mode_n << ISPCCDC_LSC_GAIN_MODE_N_SHIFT;
	reg |= cfg->gain_mode_m << ISPCCDC_LSC_GAIN_MODE_M_SHIFT;
	reg |= cfg->gain_format << ISPCCDC_LSC_GAIN_FORMAT_SHIFT;
	isp_reg_writel(isp, reg, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG);

	reg = 0;
	reg &= ~ISPCCDC_LSC_INITIAL_X_MASK;
	reg |= cfg->initial_x << ISPCCDC_LSC_INITIAL_X_SHIFT;
	reg &= ~ISPCCDC_LSC_INITIAL_Y_MASK;
	reg |= cfg->initial_y << ISPCCDC_LSC_INITIAL_Y_SHIFT;
	isp_reg_writel(isp, reg, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_LSC_INITIAL);
}