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
typedef  scalar_t__ uint ;
struct drm_mode_config {int /*<<< orphan*/  gamma_lut_size_property; int /*<<< orphan*/  gamma_lut_property; int /*<<< orphan*/  ctm_property; int /*<<< orphan*/  degamma_lut_size_property; int /*<<< orphan*/  degamma_lut_property; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_crtc {int /*<<< orphan*/  base; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void drm_crtc_enable_color_mgmt(struct drm_crtc *crtc,
				uint degamma_lut_size,
				bool has_ctm,
				uint gamma_lut_size)
{
	struct drm_device *dev = crtc->dev;
	struct drm_mode_config *config = &dev->mode_config;

	if (degamma_lut_size) {
		drm_object_attach_property(&crtc->base,
					   config->degamma_lut_property, 0);
		drm_object_attach_property(&crtc->base,
					   config->degamma_lut_size_property,
					   degamma_lut_size);
	}

	if (has_ctm)
		drm_object_attach_property(&crtc->base,
					   config->ctm_property, 0);

	if (gamma_lut_size) {
		drm_object_attach_property(&crtc->base,
					   config->gamma_lut_property, 0);
		drm_object_attach_property(&crtc->base,
					   config->gamma_lut_size_property,
					   gamma_lut_size);
	}
}