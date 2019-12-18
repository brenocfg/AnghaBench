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
struct ispstat {scalar_t__ state; int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPHIST_CNT ; 
 int /*<<< orphan*/  ISPHIST_CNT_CLEAR ; 
 scalar_t__ ISPSTAT_DISABLED ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int /*<<< orphan*/  isp_reg_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_hist_dma_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_stat_dma_isr (struct ispstat*) ; 

__attribute__((used)) static void hist_dma_cb(void *data)
{
	struct ispstat *hist = data;

	/* FIXME: The DMA engine API can't report transfer errors :-/ */

	isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CLEAR);

	omap3isp_stat_dma_isr(hist);
	if (hist->state != ISPSTAT_DISABLED)
		omap3isp_hist_dma_done(hist->isp);
}