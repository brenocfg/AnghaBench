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
struct isp_device {int dummy; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_PCR ; 
 int ISPCCDC_PCR_BUSY ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

int omap3isp_ccdc_busy(struct isp_ccdc_device *ccdc)
{
	struct isp_device *isp = to_isp_device(ccdc);

	return isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_PCR) &
		ISPCCDC_PCR_BUSY;
}