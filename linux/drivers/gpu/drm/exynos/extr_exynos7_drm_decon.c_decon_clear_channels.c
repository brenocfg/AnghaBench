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
typedef  int u32 ;
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {int /*<<< orphan*/  crtc; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WINCON (unsigned int) ; 
 int WINCONx_ENWIN ; 
 unsigned int WINDOWS_NR ; 
 int /*<<< orphan*/  decon_wait_for_vblank (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void decon_clear_channels(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	unsigned int win, ch_enabled = 0;

	/* Check if any channel is enabled. */
	for (win = 0; win < WINDOWS_NR; win++) {
		u32 val = readl(ctx->regs + WINCON(win));

		if (val & WINCONx_ENWIN) {
			val &= ~WINCONx_ENWIN;
			writel(val, ctx->regs + WINCON(win));
			ch_enabled = 1;
		}
	}

	/* Wait for vsync, as disable channel takes effect at next vsync */
	if (ch_enabled)
		decon_wait_for_vblank(ctx->crtc);
}