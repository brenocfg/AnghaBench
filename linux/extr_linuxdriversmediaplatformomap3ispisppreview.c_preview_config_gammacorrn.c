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
struct omap3isp_prev_gtables {int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
struct prev_params {struct omap3isp_prev_gtables gamma; } ;
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_BLUEGAMMA_TABLE_ADDR ; 
 int /*<<< orphan*/  ISPPRV_GREENGAMMA_TABLE_ADDR ; 
 int /*<<< orphan*/  ISPPRV_REDGAMMA_TABLE_ADDR ; 
 int /*<<< orphan*/  ISPPRV_SET_TBL_ADDR ; 
 int /*<<< orphan*/  ISPPRV_SET_TBL_DATA ; 
 unsigned int OMAP3ISP_PREV_GAMMA_TBL_SIZE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void
preview_config_gammacorrn(struct isp_prev_device *prev,
			  const struct prev_params *params)
{
	struct isp_device *isp = to_isp_device(prev);
	const struct omap3isp_prev_gtables *gt = &params->gamma;
	unsigned int i;

	isp_reg_writel(isp, ISPPRV_REDGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	for (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_writel(isp, gt->red[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);

	isp_reg_writel(isp, ISPPRV_GREENGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	for (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_writel(isp, gt->green[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);

	isp_reg_writel(isp, ISPPRV_BLUEGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	for (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_writel(isp, gt->blue[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);
}