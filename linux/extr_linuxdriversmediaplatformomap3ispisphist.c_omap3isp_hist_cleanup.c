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
struct ispstat {scalar_t__ dma_ch; } ;
struct isp_device {struct ispstat isp_hist; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  omap3isp_stat_cleanup (struct ispstat*) ; 

void omap3isp_hist_cleanup(struct isp_device *isp)
{
	struct ispstat *hist = &isp->isp_hist;

	if (hist->dma_ch)
		dma_release_channel(hist->dma_ch);

	omap3isp_stat_cleanup(hist);
}