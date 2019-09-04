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
struct omap_encoder {struct omap_dss_device* dssdev; } ;
struct omap_dss_driver {int (* enable ) (struct omap_dss_device*) ;} ;
struct omap_dss_device {int /*<<< orphan*/  name; struct omap_dss_driver* driver; } ;
struct drm_encoder {TYPE_1__* dev; int /*<<< orphan*/  crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_crtc_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_crtc_timings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_encoder_update (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct omap_dss_device*) ; 
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void omap_encoder_enable(struct drm_encoder *encoder)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);
	struct omap_dss_device *dssdev = omap_encoder->dssdev;
	struct omap_dss_driver *dssdrv = dssdev->driver;
	int r;

	omap_encoder_update(encoder, omap_crtc_channel(encoder->crtc),
			    omap_crtc_timings(encoder->crtc));

	r = dssdrv->enable(dssdev);
	if (r)
		dev_err(encoder->dev->dev,
			"Failed to enable display '%s': %d\n",
			dssdev->name, r);
}