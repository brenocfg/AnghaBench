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
struct omap_encoder {struct omap_dss_device* dssdev; } ;
struct omap_dss_driver {int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;
struct omap_dss_device {struct omap_dss_driver* driver; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void omap_encoder_disable(struct drm_encoder *encoder)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);
	struct omap_dss_device *dssdev = omap_encoder->dssdev;
	struct omap_dss_driver *dssdrv = dssdev->driver;

	dssdrv->disable(dssdev);
}