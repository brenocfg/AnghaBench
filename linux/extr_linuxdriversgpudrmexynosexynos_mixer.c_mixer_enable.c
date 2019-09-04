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
struct mixer_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 int /*<<< orphan*/  MXR_BIT_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_CLEAR_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_EN ; 
 int /*<<< orphan*/  MXR_INT_EN_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_STATUS ; 
 int /*<<< orphan*/  MXR_STATUS ; 
 int /*<<< orphan*/  MXR_STATUS_SOFT_RESET ; 
 int /*<<< orphan*/  exynos_drm_pipe_clk_enable (struct exynos_drm_crtc*,int) ; 
 int /*<<< orphan*/  mixer_commit (struct mixer_context*) ; 
 int /*<<< orphan*/  mixer_disable_sync (struct mixer_context*) ; 
 int /*<<< orphan*/  mixer_enable_sync (struct mixer_context*) ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_win_reset (struct mixer_context*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_enable(struct exynos_drm_crtc *crtc)
{
	struct mixer_context *ctx = crtc->ctx;

	if (test_bit(MXR_BIT_POWERED, &ctx->flags))
		return;

	pm_runtime_get_sync(ctx->dev);

	exynos_drm_pipe_clk_enable(crtc, true);

	mixer_disable_sync(ctx);

	mixer_reg_writemask(ctx, MXR_STATUS, ~0, MXR_STATUS_SOFT_RESET);

	if (test_bit(MXR_BIT_VSYNC, &ctx->flags)) {
		mixer_reg_writemask(ctx, MXR_INT_STATUS, ~0,
					MXR_INT_CLEAR_VSYNC);
		mixer_reg_writemask(ctx, MXR_INT_EN, ~0, MXR_INT_EN_VSYNC);
	}
	mixer_win_reset(ctx);

	mixer_commit(ctx);

	mixer_enable_sync(ctx);

	set_bit(MXR_BIT_POWERED, &ctx->flags);
}