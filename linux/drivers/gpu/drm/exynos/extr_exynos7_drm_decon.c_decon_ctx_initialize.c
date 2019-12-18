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
struct drm_device {int dummy; } ;
struct decon_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  crtc; struct drm_device* drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  decon_clear_channels (int /*<<< orphan*/ ) ; 
 int exynos_drm_register_dma (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decon_ctx_initialize(struct decon_context *ctx,
			struct drm_device *drm_dev)
{
	ctx->drm_dev = drm_dev;

	decon_clear_channels(ctx->crtc);

	return exynos_drm_register_dma(drm_dev, ctx->dev);
}