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
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct drm_connector {int interlace_allowed; int polled; scalar_t__ doublescan_allowed; } ;
struct omap_connector {void* hpd; struct drm_connector base; void* output; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DSS_DEVICE_OP_DETECT ; 
 int /*<<< orphan*/  OMAP_DSS_DEVICE_OP_HPD ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct omap_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_connector_destroy (struct drm_connector*) ; 
 struct omap_dss_device* omap_connector_find_device (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_connector_funcs ; 
 int /*<<< orphan*/  omap_connector_get_type (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omap_connector_helper_funcs ; 
 void* omapdss_device_get (struct omap_dss_device*) ; 

struct drm_connector *omap_connector_init(struct drm_device *dev,
					  struct omap_dss_device *output,
					  struct drm_encoder *encoder)
{
	struct drm_connector *connector = NULL;
	struct omap_connector *omap_connector;
	struct omap_dss_device *dssdev;

	DBG("%s", output->name);

	omap_connector = kzalloc(sizeof(*omap_connector), GFP_KERNEL);
	if (!omap_connector)
		goto fail;

	omap_connector->output = omapdss_device_get(output);

	connector = &omap_connector->base;
	connector->interlace_allowed = 1;
	connector->doublescan_allowed = 0;

	drm_connector_init(dev, connector, &omap_connector_funcs,
			   omap_connector_get_type(output));
	drm_connector_helper_add(connector, &omap_connector_helper_funcs);

	/*
	 * Initialize connector status handling. First try to find a device that
	 * supports hot-plug reporting. If it fails, fall back to a device that
	 * support polling. If that fails too, we don't support hot-plug
	 * detection at all.
	 */
	dssdev = omap_connector_find_device(connector, OMAP_DSS_DEVICE_OP_HPD);
	if (dssdev) {
		omap_connector->hpd = omapdss_device_get(dssdev);
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	} else {
		dssdev = omap_connector_find_device(connector,
						    OMAP_DSS_DEVICE_OP_DETECT);
		if (dssdev)
			connector->polled = DRM_CONNECTOR_POLL_CONNECT |
					    DRM_CONNECTOR_POLL_DISCONNECT;
	}

	return connector;

fail:
	if (connector)
		omap_connector_destroy(connector);

	return NULL;
}