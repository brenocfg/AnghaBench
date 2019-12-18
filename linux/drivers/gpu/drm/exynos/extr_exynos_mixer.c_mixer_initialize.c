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
struct mixer_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; struct drm_device* drm_dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MXR_BIT_VP_ENABLED ; 
 int exynos_drm_register_dma (struct drm_device*,int /*<<< orphan*/ ) ; 
 int mixer_resources_init (struct mixer_context*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vp_resources_init (struct mixer_context*) ; 

__attribute__((used)) static int mixer_initialize(struct mixer_context *mixer_ctx,
			struct drm_device *drm_dev)
{
	int ret;

	mixer_ctx->drm_dev = drm_dev;

	/* acquire resources: regs, irqs, clocks */
	ret = mixer_resources_init(mixer_ctx);
	if (ret) {
		DRM_DEV_ERROR(mixer_ctx->dev,
			      "mixer_resources_init failed ret=%d\n", ret);
		return ret;
	}

	if (test_bit(MXR_BIT_VP_ENABLED, &mixer_ctx->flags)) {
		/* acquire vp resources: regs, irqs, clocks */
		ret = vp_resources_init(mixer_ctx);
		if (ret) {
			DRM_DEV_ERROR(mixer_ctx->dev,
				      "vp_resources_init failed ret=%d\n", ret);
			return ret;
		}
	}

	return exynos_drm_register_dma(drm_dev, mixer_ctx->dev);
}