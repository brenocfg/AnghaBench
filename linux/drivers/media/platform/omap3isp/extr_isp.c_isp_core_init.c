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
struct isp_device {scalar_t__ revision; scalar_t__ autoidle; } ;

/* Variables and functions */
 int ISPCTRL_SBL_AUTOIDLE ; 
 int ISPCTRL_SYNC_DETECT_VSRISE ; 
 int /*<<< orphan*/  ISP_CTRL ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  ISP_SYSCONFIG ; 
 int ISP_SYSCONFIG_AUTOIDLE ; 
 int ISP_SYSCONFIG_MIDLEMODE_FORCESTANDBY ; 
 int ISP_SYSCONFIG_MIDLEMODE_SHIFT ; 
 int ISP_SYSCONFIG_MIDLEMODE_SMARTSTANDBY ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_MAIN ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_core_init(struct isp_device *isp, int idle)
{
	isp_reg_writel(isp,
		       ((idle ? ISP_SYSCONFIG_MIDLEMODE_SMARTSTANDBY :
				ISP_SYSCONFIG_MIDLEMODE_FORCESTANDBY) <<
			ISP_SYSCONFIG_MIDLEMODE_SHIFT) |
			((isp->revision == ISP_REVISION_15_0) ?
			  ISP_SYSCONFIG_AUTOIDLE : 0),
		       OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG);

	isp_reg_writel(isp,
		       (isp->autoidle ? ISPCTRL_SBL_AUTOIDLE : 0) |
		       ISPCTRL_SYNC_DETECT_VSRISE,
		       OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
}