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
struct omap3isp_prev_wbal {int dgain; int coef0; int coef1; int coef2; int coef3; } ;
struct prev_params {struct omap3isp_prev_wbal wbal; } ;
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_WBGAIN ; 
 int ISPPRV_WBGAIN_COEF0_SHIFT ; 
 int ISPPRV_WBGAIN_COEF1_SHIFT ; 
 int ISPPRV_WBGAIN_COEF2_SHIFT ; 
 int ISPPRV_WBGAIN_COEF3_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_WBSEL ; 
 int ISPPRV_WBSEL_COEF0 ; 
 int ISPPRV_WBSEL_COEF1 ; 
 int ISPPRV_WBSEL_COEF2 ; 
 int ISPPRV_WBSEL_COEF3 ; 
 int ISPPRV_WBSEL_N0_0_SHIFT ; 
 int ISPPRV_WBSEL_N0_1_SHIFT ; 
 int ISPPRV_WBSEL_N0_2_SHIFT ; 
 int ISPPRV_WBSEL_N0_3_SHIFT ; 
 int ISPPRV_WBSEL_N1_0_SHIFT ; 
 int ISPPRV_WBSEL_N1_1_SHIFT ; 
 int ISPPRV_WBSEL_N1_2_SHIFT ; 
 int ISPPRV_WBSEL_N1_3_SHIFT ; 
 int ISPPRV_WBSEL_N2_0_SHIFT ; 
 int ISPPRV_WBSEL_N2_1_SHIFT ; 
 int ISPPRV_WBSEL_N2_2_SHIFT ; 
 int ISPPRV_WBSEL_N2_3_SHIFT ; 
 int ISPPRV_WBSEL_N3_0_SHIFT ; 
 int ISPPRV_WBSEL_N3_1_SHIFT ; 
 int ISPPRV_WBSEL_N3_2_SHIFT ; 
 int ISPPRV_WBSEL_N3_3_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_WB_DGAIN ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void
preview_config_whitebalance(struct isp_prev_device *prev,
			    const struct prev_params *params)
{
	struct isp_device *isp = to_isp_device(prev);
	const struct omap3isp_prev_wbal *wbal = &params->wbal;
	u32 val;

	isp_reg_writel(isp, wbal->dgain, OMAP3_ISP_IOMEM_PREV, ISPPRV_WB_DGAIN);

	val = wbal->coef0 << ISPPRV_WBGAIN_COEF0_SHIFT;
	val |= wbal->coef1 << ISPPRV_WBGAIN_COEF1_SHIFT;
	val |= wbal->coef2 << ISPPRV_WBGAIN_COEF2_SHIFT;
	val |= wbal->coef3 << ISPPRV_WBGAIN_COEF3_SHIFT;
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_WBGAIN);

	isp_reg_writel(isp,
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N0_0_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N0_1_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N0_2_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N0_3_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N1_0_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N1_1_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N1_2_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N1_3_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N2_0_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N2_1_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N2_2_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N2_3_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N3_0_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N3_1_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N3_2_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N3_3_SHIFT,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_WBSEL);
}