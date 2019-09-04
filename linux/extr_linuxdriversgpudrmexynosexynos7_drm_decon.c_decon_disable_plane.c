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
typedef  int /*<<< orphan*/  u32 ;
struct exynos_drm_plane {unsigned int index; } ;
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {scalar_t__ regs; scalar_t__ suspended; } ;

/* Variables and functions */
 scalar_t__ DECON_UPDATE ; 
 int /*<<< orphan*/  DECON_UPDATE_STANDALONE_F ; 
 scalar_t__ WINCON (unsigned int) ; 
 int /*<<< orphan*/  WINCONx_ENWIN ; 
 int /*<<< orphan*/  decon_shadow_protect_win (struct decon_context*,unsigned int,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decon_disable_plane(struct exynos_drm_crtc *crtc,
				struct exynos_drm_plane *plane)
{
	struct decon_context *ctx = crtc->ctx;
	unsigned int win = plane->index;
	u32 val;

	if (ctx->suspended)
		return;

	/* protect windows */
	decon_shadow_protect_win(ctx, win, true);

	/* wincon */
	val = readl(ctx->regs + WINCON(win));
	val &= ~WINCONx_ENWIN;
	writel(val, ctx->regs + WINCON(win));

	val = readl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	writel(val, ctx->regs + DECON_UPDATE);
}