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
struct drm_connector {int /*<<< orphan*/  polled; } ;
struct vidi_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; struct drm_connector connector; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vidi_context* encoder_to_vidi (struct drm_encoder*) ; 
 int /*<<< orphan*/  vidi_connector_funcs ; 
 int /*<<< orphan*/  vidi_connector_helper_funcs ; 

__attribute__((used)) static int vidi_create_connector(struct drm_encoder *encoder)
{
	struct vidi_context *ctx = encoder_to_vidi(encoder);
	struct drm_connector *connector = &ctx->connector;
	int ret;

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(ctx->drm_dev, connector,
			&vidi_connector_funcs, DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret) {
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to initialize connector with drm\n");
		return ret;
	}

	drm_connector_helper_add(connector, &vidi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	return 0;
}