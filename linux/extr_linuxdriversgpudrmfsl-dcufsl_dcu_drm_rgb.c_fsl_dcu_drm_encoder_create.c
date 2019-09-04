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
struct drm_encoder {int possible_crtcs; } ;
struct fsl_dcu_drm_device {int /*<<< orphan*/  drm; scalar_t__ tcon; struct drm_encoder encoder; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_LVDS ; 
 int drm_encoder_init (int /*<<< orphan*/ ,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encoder_funcs ; 
 int /*<<< orphan*/  fsl_tcon_bypass_enable (scalar_t__) ; 

int fsl_dcu_drm_encoder_create(struct fsl_dcu_drm_device *fsl_dev,
			       struct drm_crtc *crtc)
{
	struct drm_encoder *encoder = &fsl_dev->encoder;
	int ret;

	encoder->possible_crtcs = 1;

	/* Use bypass mode for parallel RGB/LVDS encoder */
	if (fsl_dev->tcon)
		fsl_tcon_bypass_enable(fsl_dev->tcon);

	ret = drm_encoder_init(fsl_dev->drm, encoder, &encoder_funcs,
			       DRM_MODE_ENCODER_LVDS, NULL);
	if (ret < 0)
		return ret;

	return 0;
}