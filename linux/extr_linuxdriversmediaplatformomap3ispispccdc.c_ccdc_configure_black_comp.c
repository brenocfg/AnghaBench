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
struct isp_device {int dummy; } ;
struct TYPE_2__ {int b_mg; int gb_g; int gr_cy; int r_ye; } ;
struct isp_ccdc_device {TYPE_1__ blcomp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_BLKCMP ; 
 int ISPCCDC_BLKCMP_B_MG_SHIFT ; 
 int ISPCCDC_BLKCMP_GB_G_SHIFT ; 
 int ISPCCDC_BLKCMP_GR_CY_SHIFT ; 
 int ISPCCDC_BLKCMP_R_YE_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_configure_black_comp(struct isp_ccdc_device *ccdc)
{
	struct isp_device *isp = to_isp_device(ccdc);
	u32 blcomp;

	blcomp  = ccdc->blcomp.b_mg << ISPCCDC_BLKCMP_B_MG_SHIFT;
	blcomp |= ccdc->blcomp.gb_g << ISPCCDC_BLKCMP_GB_G_SHIFT;
	blcomp |= ccdc->blcomp.gr_cy << ISPCCDC_BLKCMP_GR_CY_SHIFT;
	blcomp |= ccdc->blcomp.r_ye << ISPCCDC_BLKCMP_R_YE_SHIFT;

	isp_reg_writel(isp, blcomp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_BLKCMP);
}