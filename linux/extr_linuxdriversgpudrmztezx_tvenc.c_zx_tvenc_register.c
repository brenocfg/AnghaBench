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
struct drm_connector {int interlace_allowed; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct zx_tvenc {struct drm_connector connector; struct drm_encoder encoder; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Composite ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TVDAC ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zx_tvenc_connector_funcs ; 
 int /*<<< orphan*/  zx_tvenc_connector_helper_funcs ; 
 int /*<<< orphan*/  zx_tvenc_encoder_funcs ; 
 int /*<<< orphan*/  zx_tvenc_encoder_helper_funcs ; 

__attribute__((used)) static int zx_tvenc_register(struct drm_device *drm, struct zx_tvenc *tvenc)
{
	struct drm_encoder *encoder = &tvenc->encoder;
	struct drm_connector *connector = &tvenc->connector;

	/*
	 * The tvenc is designed to use aux channel, as there is a deflicker
	 * block for the channel.
	 */
	encoder->possible_crtcs = BIT(1);

	drm_encoder_init(drm, encoder, &zx_tvenc_encoder_funcs,
			 DRM_MODE_ENCODER_TVDAC, NULL);
	drm_encoder_helper_add(encoder, &zx_tvenc_encoder_helper_funcs);

	connector->interlace_allowed = true;

	drm_connector_init(drm, connector, &zx_tvenc_connector_funcs,
			   DRM_MODE_CONNECTOR_Composite);
	drm_connector_helper_add(connector, &zx_tvenc_connector_helper_funcs);

	drm_connector_attach_encoder(connector, encoder);

	return 0;
}