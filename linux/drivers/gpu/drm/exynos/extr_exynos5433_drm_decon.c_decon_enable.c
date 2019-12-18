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
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {int /*<<< orphan*/  crtc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  decon_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_swreset (struct decon_context*) ; 
 int /*<<< orphan*/  exynos_drm_pipe_clk_enable (struct exynos_drm_crtc*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_enable(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;

	pm_runtime_get_sync(ctx->dev);

	exynos_drm_pipe_clk_enable(crtc, true);

	decon_swreset(ctx);

	decon_commit(ctx->crtc);
}