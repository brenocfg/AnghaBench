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
struct prev_params {int contrast; } ;
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_CNT_BRT ; 
 int ISPPRV_CNT_BRT_CNT_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void
preview_config_contrast(struct isp_prev_device *prev,
			const struct prev_params *params)
{
	struct isp_device *isp = to_isp_device(prev);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_CNT_BRT,
			0xff << ISPPRV_CNT_BRT_CNT_SHIFT,
			params->contrast << ISPPRV_CNT_BRT_CNT_SHIFT);
}