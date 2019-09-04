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
struct mixer_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; int /*<<< orphan*/ * planes; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int MIXER_WIN_NR ; 
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_drm_pipe_clk_enable (struct exynos_drm_crtc*,int) ; 
 int /*<<< orphan*/  mixer_disable_plane (struct exynos_drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_regs_dump (struct mixer_context*) ; 
 int /*<<< orphan*/  mixer_stop (struct mixer_context*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_disable(struct exynos_drm_crtc *crtc)
{
	struct mixer_context *ctx = crtc->ctx;
	int i;

	if (!test_bit(MXR_BIT_POWERED, &ctx->flags))
		return;

	mixer_stop(ctx);
	mixer_regs_dump(ctx);

	for (i = 0; i < MIXER_WIN_NR; i++)
		mixer_disable_plane(crtc, &ctx->planes[i]);

	exynos_drm_pipe_clk_enable(crtc, false);

	pm_runtime_put(ctx->dev);

	clear_bit(MXR_BIT_POWERED, &ctx->flags);
}