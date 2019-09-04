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
struct fimd_context {int suspended; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/ * planes; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;

/* Variables and functions */
 scalar_t__ VIDCON0 ; 
 int WINDOWS_NR ; 
 int /*<<< orphan*/  fimd_disable_plane (struct exynos_drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimd_disable_vblank (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  fimd_enable_vblank (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  fimd_wait_for_vblank (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fimd_disable(struct exynos_drm_crtc *crtc)
{
	struct fimd_context *ctx = crtc->ctx;
	int i;

	if (ctx->suspended)
		return;

	/*
	 * We need to make sure that all windows are disabled before we
	 * suspend that connector. Otherwise we might try to scan from
	 * a destroyed buffer later.
	 */
	for (i = 0; i < WINDOWS_NR; i++)
		fimd_disable_plane(crtc, &ctx->planes[i]);

	fimd_enable_vblank(crtc);
	fimd_wait_for_vblank(crtc);
	fimd_disable_vblank(crtc);

	writel(0, ctx->regs + VIDCON0);

	pm_runtime_put_sync(ctx->dev);
	ctx->suspended = true;
}