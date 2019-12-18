#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {int /*<<< orphan*/  base; TYPE_1__ display_info; } ;
struct TYPE_12__ {struct drm_encoder* encoder; struct drm_connector connector; } ;
struct shmob_drm_device {TYPE_5__ connector; TYPE_7__* ddev; TYPE_3__* pdata; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dpms_property; } ;
struct TYPE_13__ {TYPE_4__ mode_config; } ;
struct TYPE_9__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct TYPE_10__ {TYPE_2__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  connector_funcs ; 
 int /*<<< orphan*/  connector_helper_funcs ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (TYPE_7__*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_helper_connector_dpms (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmob_drm_backlight_exit (TYPE_5__*) ; 
 int shmob_drm_backlight_init (TYPE_5__*) ; 

int shmob_drm_connector_create(struct shmob_drm_device *sdev,
			       struct drm_encoder *encoder)
{
	struct drm_connector *connector = &sdev->connector.connector;
	int ret;

	sdev->connector.encoder = encoder;

	connector->display_info.width_mm = sdev->pdata->panel.width_mm;
	connector->display_info.height_mm = sdev->pdata->panel.height_mm;

	ret = drm_connector_init(sdev->ddev, connector, &connector_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	if (ret < 0)
		return ret;

	drm_connector_helper_add(connector, &connector_helper_funcs);

	ret = shmob_drm_backlight_init(&sdev->connector);
	if (ret < 0)
		goto err_cleanup;

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret < 0)
		goto err_backlight;

	drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
	drm_object_property_set_value(&connector->base,
		sdev->ddev->mode_config.dpms_property, DRM_MODE_DPMS_OFF);

	return 0;

err_backlight:
	shmob_drm_backlight_exit(&sdev->connector);
err_cleanup:
	drm_connector_cleanup(connector);
	return ret;
}