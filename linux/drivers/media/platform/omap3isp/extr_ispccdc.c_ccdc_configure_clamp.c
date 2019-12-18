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
struct TYPE_2__ {int obgain; int oblen; int oblines; int obstpixel; int dcsubval; } ;
struct isp_ccdc_device {scalar_t__ obclamp; TYPE_1__ clamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_CLAMP ; 
 int /*<<< orphan*/  ISPCCDC_CLAMP_CLAMPEN ; 
 int ISPCCDC_CLAMP_OBGAIN_SHIFT ; 
 int ISPCCDC_CLAMP_OBSLEN_SHIFT ; 
 int ISPCCDC_CLAMP_OBSLN_SHIFT ; 
 int ISPCCDC_CLAMP_OBST_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_DCSUB ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_configure_clamp(struct isp_ccdc_device *ccdc)
{
	struct isp_device *isp = to_isp_device(ccdc);
	u32 clamp;

	if (ccdc->obclamp) {
		clamp  = ccdc->clamp.obgain << ISPCCDC_CLAMP_OBGAIN_SHIFT;
		clamp |= ccdc->clamp.oblen << ISPCCDC_CLAMP_OBSLEN_SHIFT;
		clamp |= ccdc->clamp.oblines << ISPCCDC_CLAMP_OBSLN_SHIFT;
		clamp |= ccdc->clamp.obstpixel << ISPCCDC_CLAMP_OBST_SHIFT;
		isp_reg_writel(isp, clamp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CLAMP);
	} else {
		isp_reg_writel(isp, ccdc->clamp.dcsubval,
			       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_DCSUB);
	}

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CLAMP,
			ISPCCDC_CLAMP_CLAMPEN,
			ccdc->obclamp ? ISPCCDC_CLAMP_CLAMPEN : 0);
}