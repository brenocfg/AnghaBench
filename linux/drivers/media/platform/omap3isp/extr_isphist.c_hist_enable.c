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
 int /*<<< orphan*/  ISPHIST_PCR ; 
 int /*<<< orphan*/  ISPHIST_PCR_ENABLE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int /*<<< orphan*/  OMAP3_ISP_SUBCLK_HIST ; 
 int /*<<< orphan*/  isp_reg_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_enable(struct ispstat *hist, int enable)
{
	if (enable) {
		isp_reg_set(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR,
			    ISPHIST_PCR_ENABLE);
		omap3isp_subclk_enable(hist->isp, OMAP3_ISP_SUBCLK_HIST);
	} else {
		isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR,
			    ISPHIST_PCR_ENABLE);
		omap3isp_subclk_disable(hist->isp, OMAP3_ISP_SUBCLK_HIST);
	}
}