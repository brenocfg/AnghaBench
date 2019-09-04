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
struct ispstat {int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPH3A_PCR ; 
 int /*<<< orphan*/  ISPH3A_PCR_AEW_EN ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_H3A ; 
 int /*<<< orphan*/  OMAP3_ISP_SUBCLK_AEWB ; 
 int /*<<< orphan*/  isp_reg_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void h3a_aewb_enable(struct ispstat *aewb, int enable)
{
	if (enable) {
		isp_reg_set(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AEW_EN);
		omap3isp_subclk_enable(aewb->isp, OMAP3_ISP_SUBCLK_AEWB);
	} else {
		isp_reg_clr(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AEW_EN);
		omap3isp_subclk_disable(aewb->isp, OMAP3_ISP_SUBCLK_AEWB);
	}
}