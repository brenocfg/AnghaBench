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
struct omap3isp_prev_hmed {int odddist; int evendist; int thres; } ;
struct prev_params {struct omap3isp_prev_hmed hmed; } ;
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_HMED ; 
 int ISPPRV_HMED_EVENDIST ; 
 int ISPPRV_HMED_ODDDIST ; 
 int ISPPRV_HMED_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_config_hmed(struct isp_prev_device *prev,
				const struct prev_params *params)
{
	struct isp_device *isp = to_isp_device(prev);
	const struct omap3isp_prev_hmed *hmed = &params->hmed;

	isp_reg_writel(isp, (hmed->odddist == 1 ? 0 : ISPPRV_HMED_ODDDIST) |
		       (hmed->evendist == 1 ? 0 : ISPPRV_HMED_EVENDIST) |
		       (hmed->thres << ISPPRV_HMED_THRESHOLD_SHIFT),
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_HMED);
}