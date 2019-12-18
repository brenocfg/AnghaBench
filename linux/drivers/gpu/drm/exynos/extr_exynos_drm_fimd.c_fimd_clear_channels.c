#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fimd_context {int suspended; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  lcd_clk; int /*<<< orphan*/  crtc; TYPE_1__* driver_data; scalar_t__ regs; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;
struct TYPE_2__ {scalar_t__ has_shadowcon; } ;

/* Variables and functions */
 scalar_t__ WINCON (unsigned int) ; 
 int WINCONx_ENWIN ; 
 unsigned int WINDOWS_NR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_disable_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_enable_shadow_channel_path (struct fimd_context*,unsigned int,int) ; 
 int /*<<< orphan*/  fimd_enable_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_enable_video_output (struct fimd_context*,unsigned int,int) ; 
 int /*<<< orphan*/  fimd_wait_for_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void fimd_clear_channels(struct exynos_drm_crtc *crtc)
{
	struct fimd_context *ctx = crtc->ctx;
	unsigned int win, ch_enabled = 0;

	/* Hardware is in unknown state, so ensure it gets enabled properly */
	pm_runtime_get_sync(ctx->dev);

	clk_prepare_enable(ctx->bus_clk);
	clk_prepare_enable(ctx->lcd_clk);

	/* Check if any channel is enabled. */
	for (win = 0; win < WINDOWS_NR; win++) {
		u32 val = readl(ctx->regs + WINCON(win));

		if (val & WINCONx_ENWIN) {
			fimd_enable_video_output(ctx, win, false);

			if (ctx->driver_data->has_shadowcon)
				fimd_enable_shadow_channel_path(ctx, win,
								false);

			ch_enabled = 1;
		}
	}

	/* Wait for vsync, as disable channel takes effect at next vsync */
	if (ch_enabled) {
		ctx->suspended = false;

		fimd_enable_vblank(ctx->crtc);
		fimd_wait_for_vblank(ctx->crtc);
		fimd_disable_vblank(ctx->crtc);

		ctx->suspended = true;
	}

	clk_disable_unprepare(ctx->lcd_clk);
	clk_disable_unprepare(ctx->bus_clk);

	pm_runtime_put(ctx->dev);
}