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
struct exynos_drm_crtc {int /*<<< orphan*/  base; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; int /*<<< orphan*/  dev; } ;
typedef  enum exynos_drm_output_type { ____Placeholder_exynos_drm_output_type } exynos_drm_output_type ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct exynos_drm_crtc*) ; 
 int PTR_ERR (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_mask (int /*<<< orphan*/ *) ; 
 struct exynos_drm_crtc* exynos_drm_crtc_get_by_type (int /*<<< orphan*/ ,int) ; 

int exynos_drm_set_possible_crtcs(struct drm_encoder *encoder,
		enum exynos_drm_output_type out_type)
{
	struct exynos_drm_crtc *crtc = exynos_drm_crtc_get_by_type(encoder->dev,
						out_type);

	if (IS_ERR(crtc))
		return PTR_ERR(crtc);

	encoder->possible_crtcs = drm_crtc_mask(&crtc->base);

	return 0;
}