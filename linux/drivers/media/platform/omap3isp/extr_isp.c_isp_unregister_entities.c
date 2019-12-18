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
struct isp_device {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  isp_hist; int /*<<< orphan*/  isp_af; int /*<<< orphan*/  isp_aewb; int /*<<< orphan*/  isp_res; int /*<<< orphan*/  isp_prev; int /*<<< orphan*/  isp_ccdc; int /*<<< orphan*/  isp_ccp2; int /*<<< orphan*/  isp_csi2a; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_ccdc_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_ccp2_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_csi2_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_preview_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_resizer_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_stat_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp_unregister_entities(struct isp_device *isp)
{
	media_device_unregister(&isp->media_dev);

	omap3isp_csi2_unregister_entities(&isp->isp_csi2a);
	omap3isp_ccp2_unregister_entities(&isp->isp_ccp2);
	omap3isp_ccdc_unregister_entities(&isp->isp_ccdc);
	omap3isp_preview_unregister_entities(&isp->isp_prev);
	omap3isp_resizer_unregister_entities(&isp->isp_res);
	omap3isp_stat_unregister_entities(&isp->isp_aewb);
	omap3isp_stat_unregister_entities(&isp->isp_af);
	omap3isp_stat_unregister_entities(&isp->isp_hist);

	v4l2_device_unregister(&isp->v4l2_dev);
	media_device_cleanup(&isp->media_dev);
}