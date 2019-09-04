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
typedef  scalar_t__ u32 ;
struct drm_encoder {scalar_t__ possible_crtcs; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_of_find_possible_crtcs (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_encoder_funcs ; 
 int /*<<< orphan*/  dw_encoder_helper_funcs ; 

__attribute__((used)) static int dw_drm_encoder_init(struct device *dev,
			       struct drm_device *drm_dev,
			       struct drm_encoder *encoder)
{
	int ret;
	u32 crtc_mask = drm_of_find_possible_crtcs(drm_dev, dev->of_node);

	if (!crtc_mask) {
		DRM_ERROR("failed to find crtc mask\n");
		return -EINVAL;
	}

	encoder->possible_crtcs = crtc_mask;
	ret = drm_encoder_init(drm_dev, encoder, &dw_encoder_funcs,
			       DRM_MODE_ENCODER_DSI, NULL);
	if (ret) {
		DRM_ERROR("failed to init dsi encoder\n");
		return ret;
	}

	drm_encoder_helper_add(encoder, &dw_encoder_helper_funcs);

	return 0;
}