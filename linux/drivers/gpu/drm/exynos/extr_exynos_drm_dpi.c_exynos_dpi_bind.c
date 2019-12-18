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
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_LCD ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* encoder_to_dpi (struct drm_encoder*) ; 
 int exynos_dpi_create_connector (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dpi_encoder_funcs ; 
 int /*<<< orphan*/  exynos_dpi_encoder_helper_funcs ; 
 int exynos_drm_set_possible_crtcs (struct drm_encoder*,int /*<<< orphan*/ ) ; 

int exynos_dpi_bind(struct drm_device *dev, struct drm_encoder *encoder)
{
	int ret;

	drm_encoder_init(dev, encoder, &exynos_dpi_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	drm_encoder_helper_add(encoder, &exynos_dpi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	if (ret < 0)
		return ret;

	ret = exynos_dpi_create_connector(encoder);
	if (ret) {
		DRM_DEV_ERROR(encoder_to_dpi(encoder)->dev,
			      "failed to create connector ret = %d\n", ret);
		drm_encoder_cleanup(encoder);
		return ret;
	}

	return 0;
}