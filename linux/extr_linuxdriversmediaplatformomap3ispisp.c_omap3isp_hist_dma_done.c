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
struct TYPE_2__ {int /*<<< orphan*/  buf_err; } ;
struct isp_device {int /*<<< orphan*/  dev; TYPE_1__ isp_hist; int /*<<< orphan*/  isp_ccdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ omap3isp_ccdc_busy (int /*<<< orphan*/ *) ; 
 scalar_t__ omap3isp_stat_pcr_busy (TYPE_1__*) ; 

void omap3isp_hist_dma_done(struct isp_device *isp)
{
	if (omap3isp_ccdc_busy(&isp->isp_ccdc) ||
	    omap3isp_stat_pcr_busy(&isp->isp_hist)) {
		/* Histogram cannot be enabled in this frame anymore */
		atomic_set(&isp->isp_hist.buf_err, 1);
		dev_dbg(isp->dev,
			"hist: Out of synchronization with CCDC. Ignoring next buffer.\n");
	}
}