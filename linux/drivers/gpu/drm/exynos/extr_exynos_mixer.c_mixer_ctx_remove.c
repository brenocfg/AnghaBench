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
struct mixer_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_drm_unregister_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_ctx_remove(struct mixer_context *mixer_ctx)
{
	exynos_drm_unregister_dma(mixer_ctx->drm_dev, mixer_ctx->dev);
}