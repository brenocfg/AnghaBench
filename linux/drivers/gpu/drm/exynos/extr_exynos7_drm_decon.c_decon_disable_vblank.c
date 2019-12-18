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
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {scalar_t__ regs; int /*<<< orphan*/  i80_if; int /*<<< orphan*/  irq_flags; scalar_t__ suspended; } ;

/* Variables and functions */
 scalar_t__ VIDINTCON0 ; 
 int /*<<< orphan*/  VIDINTCON0_INT_ENABLE ; 
 int /*<<< orphan*/  VIDINTCON0_INT_FRAME ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decon_disable_vblank(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	u32 val;

	if (ctx->suspended)
		return;

	if (test_and_clear_bit(0, &ctx->irq_flags)) {
		val = readl(ctx->regs + VIDINTCON0);

		val &= ~VIDINTCON0_INT_ENABLE;
		if (!ctx->i80_if)
			val &= ~VIDINTCON0_INT_FRAME;

		writel(val, ctx->regs + VIDINTCON0);
	}
}