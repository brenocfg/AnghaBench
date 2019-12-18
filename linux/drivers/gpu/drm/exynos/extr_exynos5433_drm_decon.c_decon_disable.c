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
struct decon_context {int out_type; int first_win; int /*<<< orphan*/  dev; int /*<<< orphan*/ * planes; int /*<<< orphan*/  irq; int /*<<< orphan*/  te_irq; } ;

/* Variables and functions */
 int I80_HW_TRG ; 
 int WINDOWS_NR ; 
 int /*<<< orphan*/  decon_disable_plane (struct exynos_drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decon_swreset (struct decon_context*) ; 
 int /*<<< orphan*/  exynos_drm_pipe_clk_enable (struct exynos_drm_crtc*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_disable(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	int i;

	if (!(ctx->out_type & I80_HW_TRG))
		synchronize_irq(ctx->te_irq);
	synchronize_irq(ctx->irq);

	/*
	 * We need to make sure that all windows are disabled before we
	 * suspend that connector. Otherwise we might try to scan from
	 * a destroyed buffer later.
	 */
	for (i = ctx->first_win; i < WINDOWS_NR; i++)
		decon_disable_plane(crtc, &ctx->planes[i]);

	decon_swreset(ctx);

	exynos_drm_pipe_clk_enable(crtc, false);

	pm_runtime_put_sync(ctx->dev);
}