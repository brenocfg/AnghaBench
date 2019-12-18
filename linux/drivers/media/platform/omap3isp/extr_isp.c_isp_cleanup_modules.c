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
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_ccdc_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_ccp2_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_csi2_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_csiphy_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_h3a_aewb_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_h3a_af_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_hist_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_preview_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_resizer_cleanup (struct isp_device*) ; 

__attribute__((used)) static void isp_cleanup_modules(struct isp_device *isp)
{
	omap3isp_h3a_aewb_cleanup(isp);
	omap3isp_h3a_af_cleanup(isp);
	omap3isp_hist_cleanup(isp);
	omap3isp_resizer_cleanup(isp);
	omap3isp_preview_cleanup(isp);
	omap3isp_ccdc_cleanup(isp);
	omap3isp_ccp2_cleanup(isp);
	omap3isp_csi2_cleanup(isp);
	omap3isp_csiphy_cleanup(isp);
}