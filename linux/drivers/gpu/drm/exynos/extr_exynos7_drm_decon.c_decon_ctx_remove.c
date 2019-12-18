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
struct decon_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_drm_unregister_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_ctx_remove(struct decon_context *ctx)
{
	/* detach this sub driver from iommu mapping if supported. */
	exynos_drm_unregister_dma(ctx->drm_dev, ctx->dev);
}