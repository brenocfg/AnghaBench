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
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct rockchip_dp_device {struct device* dev; struct drm_device* drm_dev; struct drm_encoder encoder; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_of_find_possible_crtcs (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_dp_encoder_funcs ; 
 int /*<<< orphan*/  rockchip_dp_encoder_helper_funcs ; 

__attribute__((used)) static int rockchip_dp_drm_create_encoder(struct rockchip_dp_device *dp)
{
	struct drm_encoder *encoder = &dp->encoder;
	struct drm_device *drm_dev = dp->drm_dev;
	struct device *dev = dp->dev;
	int ret;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dev->of_node);
	DRM_DEBUG_KMS("possible_crtcs = 0x%x\n", encoder->possible_crtcs);

	ret = drm_encoder_init(drm_dev, encoder, &rockchip_dp_encoder_funcs,
			       DRM_MODE_ENCODER_TMDS, NULL);
	if (ret) {
		DRM_ERROR("failed to initialize encoder with drm\n");
		return ret;
	}

	drm_encoder_helper_add(encoder, &rockchip_dp_encoder_helper_funcs);

	return 0;
}