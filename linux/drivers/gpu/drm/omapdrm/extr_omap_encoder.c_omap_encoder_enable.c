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
struct omap_encoder {struct omap_dss_device* output; } ;
struct omap_dss_device {scalar_t__ type; scalar_t__ panel; int /*<<< orphan*/  next; int /*<<< orphan*/  state; TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 scalar_t__ OMAP_DISPLAY_TYPE_DSI ; 
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_ACTIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 
 int /*<<< orphan*/  omapdss_device_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapdss_device_pre_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void omap_encoder_enable(struct drm_encoder *encoder)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);
	struct omap_dss_device *dssdev = omap_encoder->output;
	struct drm_device *dev = encoder->dev;

	dev_dbg(dev->dev, "enable(%s)\n", dssdev->name);

	/* Prepare the chain of external devices for pipeline enable. */
	omapdss_device_pre_enable(dssdev->next);

	/*
	 * Enable the internal encoder. This will enable the DSS output. The
	 * DSI is treated as an exception as DSI pipelines still use the legacy
	 * flow where the pipeline output controls the encoder.
	 */
	if (dssdev->type != OMAP_DISPLAY_TYPE_DSI) {
		dssdev->ops->enable(dssdev);
		dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;
	}

	/*
	 * Enable the chain of external devices, starting at the one at the
	 * internal encoder's output.
	 */
	omapdss_device_enable(dssdev->next);

	/* Enable the panel if present. */
	if (dssdev->panel) {
		drm_panel_prepare(dssdev->panel);
		drm_panel_enable(dssdev->panel);
	}
}