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
struct isp_device {int /*<<< orphan*/  isp_ccdc; int /*<<< orphan*/  isp_hist; int /*<<< orphan*/  isp_aewb; int /*<<< orphan*/  isp_af; } ;

/* Variables and functions */
 scalar_t__ omap3isp_ccdc_busy (int /*<<< orphan*/ *) ; 
 scalar_t__ omap3isp_stat_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_pipeline_wait_ccdc(struct isp_device *isp)
{
	return omap3isp_stat_busy(&isp->isp_af)
	    || omap3isp_stat_busy(&isp->isp_aewb)
	    || omap3isp_stat_busy(&isp->isp_hist)
	    || omap3isp_ccdc_busy(&isp->isp_ccdc);
}