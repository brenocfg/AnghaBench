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
struct decon_context {int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECON_UPDATE ; 
 int /*<<< orphan*/  DECON_WINCONx (int) ; 
 int /*<<< orphan*/  STANDALONE_UPDATE_F ; 
 int /*<<< orphan*/  WINCONx_ENWIN_F ; 
 int WINDOWS_NR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_clks_name ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_shadow_protect (struct decon_context*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void decon_clear_channels(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	int win, i, ret;

	for (i = 0; i < ARRAY_SIZE(decon_clks_name); i++) {
		ret = clk_prepare_enable(ctx->clks[i]);
		if (ret < 0)
			goto err;
	}

	decon_shadow_protect(ctx, true);
	for (win = 0; win < WINDOWS_NR; win++)
		decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, 0);
	decon_shadow_protect(ctx, false);

	decon_set_bits(ctx, DECON_UPDATE, STANDALONE_UPDATE_F, ~0);

	/* TODO: wait for possible vsync */
	msleep(50);

err:
	while (--i >= 0)
		clk_disable_unprepare(ctx->clks[i]);
}