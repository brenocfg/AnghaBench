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
struct isp_ccdc_device {int update; } ;
struct isp_device {struct isp_ccdc_device isp_ccdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_CFG ; 
 int /*<<< orphan*/  ISPCCDC_CFG_VDLC ; 
 int OMAP3ISP_CCDC_ALAW ; 
 int OMAP3ISP_CCDC_BCOMP ; 
 int OMAP3ISP_CCDC_BLCLAMP ; 
 int OMAP3ISP_CCDC_LPF ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  ccdc_apply_controls (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_configure_fpc (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3isp_ccdc_restore_context(struct isp_device *isp)
{
	struct isp_ccdc_device *ccdc = &isp->isp_ccdc;

	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG, ISPCCDC_CFG_VDLC);

	ccdc->update = OMAP3ISP_CCDC_ALAW | OMAP3ISP_CCDC_LPF
		     | OMAP3ISP_CCDC_BLCLAMP | OMAP3ISP_CCDC_BCOMP;
	ccdc_apply_controls(ccdc);
	ccdc_configure_fpc(ccdc);
}