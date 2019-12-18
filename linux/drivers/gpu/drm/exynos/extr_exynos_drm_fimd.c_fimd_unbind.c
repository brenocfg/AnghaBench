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
struct fimd_context {scalar_t__ encoder; int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; int /*<<< orphan*/  crtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fimd_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_dpi_remove (scalar_t__) ; 
 int /*<<< orphan*/  exynos_drm_unregister_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimd_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct fimd_context *ctx = dev_get_drvdata(dev);

	fimd_disable(ctx->crtc);

	exynos_drm_unregister_dma(ctx->drm_dev, ctx->dev);

	if (ctx->encoder)
		exynos_dpi_remove(ctx->encoder);
}