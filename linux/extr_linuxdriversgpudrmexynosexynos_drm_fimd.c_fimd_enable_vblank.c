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
struct fimd_context {scalar_t__ regs; scalar_t__ i80_if; int /*<<< orphan*/  irq_flags; scalar_t__ suspended; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ VIDINTCON0 ; 
 int /*<<< orphan*/  VIDINTCON0_FRAMESEL0_FRONTPORCH ; 
 int /*<<< orphan*/  VIDINTCON0_FRAMESEL0_MASK ; 
 int /*<<< orphan*/  VIDINTCON0_FRAMESEL1_MASK ; 
 int /*<<< orphan*/  VIDINTCON0_FRAMESEL1_NONE ; 
 int /*<<< orphan*/  VIDINTCON0_INT_ENABLE ; 
 int /*<<< orphan*/  VIDINTCON0_INT_FRAME ; 
 int /*<<< orphan*/  VIDINTCON0_INT_I80IFDONE ; 
 int /*<<< orphan*/  VIDINTCON0_INT_SYSMAINCON ; 
 int /*<<< orphan*/  VIDINTCON0_INT_SYSSUBCON ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fimd_enable_vblank(struct exynos_drm_crtc *crtc)
{
	struct fimd_context *ctx = crtc->ctx;
	u32 val;

	if (ctx->suspended)
		return -EPERM;

	if (!test_and_set_bit(0, &ctx->irq_flags)) {
		val = readl(ctx->regs + VIDINTCON0);

		val |= VIDINTCON0_INT_ENABLE;

		if (ctx->i80_if) {
			val |= VIDINTCON0_INT_I80IFDONE;
			val |= VIDINTCON0_INT_SYSMAINCON;
			val &= ~VIDINTCON0_INT_SYSSUBCON;
		} else {
			val |= VIDINTCON0_INT_FRAME;

			val &= ~VIDINTCON0_FRAMESEL0_MASK;
			val |= VIDINTCON0_FRAMESEL0_FRONTPORCH;
			val &= ~VIDINTCON0_FRAMESEL1_MASK;
			val |= VIDINTCON0_FRAMESEL1_NONE;
		}

		writel(val, ctx->regs + VIDINTCON0);
	}

	return 0;
}