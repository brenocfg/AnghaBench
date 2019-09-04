#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  polled; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  transfer; int /*<<< orphan*/ * dev; } ;
struct anx78xx {TYPE_3__ connector; TYPE_2__ aux; TYPE_1__* client; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DisplayPort ; 
 int ENODEV ; 
 int /*<<< orphan*/  anx78xx_aux_transfer ; 
 int /*<<< orphan*/  anx78xx_connector_funcs ; 
 int /*<<< orphan*/  anx78xx_connector_helper_funcs ; 
 struct anx78xx* bridge_to_anx78xx (struct drm_bridge*) ; 
 int drm_connector_attach_encoder (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_connector_register (TYPE_3__*) ; 
 int drm_dp_aux_register (TYPE_2__*) ; 

__attribute__((used)) static int anx78xx_bridge_attach(struct drm_bridge *bridge)
{
	struct anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	int err;

	if (!bridge->encoder) {
		DRM_ERROR("Parent encoder object not found");
		return -ENODEV;
	}

	/* Register aux channel */
	anx78xx->aux.name = "DP-AUX";
	anx78xx->aux.dev = &anx78xx->client->dev;
	anx78xx->aux.transfer = anx78xx_aux_transfer;

	err = drm_dp_aux_register(&anx78xx->aux);
	if (err < 0) {
		DRM_ERROR("Failed to register aux channel: %d\n", err);
		return err;
	}

	err = drm_connector_init(bridge->dev, &anx78xx->connector,
				 &anx78xx_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	if (err) {
		DRM_ERROR("Failed to initialize connector: %d\n", err);
		return err;
	}

	drm_connector_helper_add(&anx78xx->connector,
				 &anx78xx_connector_helper_funcs);

	err = drm_connector_register(&anx78xx->connector);
	if (err) {
		DRM_ERROR("Failed to register connector: %d\n", err);
		return err;
	}

	anx78xx->connector.polled = DRM_CONNECTOR_POLL_HPD;

	err = drm_connector_attach_encoder(&anx78xx->connector,
					   bridge->encoder);
	if (err) {
		DRM_ERROR("Failed to link up connector to encoder: %d\n", err);
		return err;
	}

	return 0;
}