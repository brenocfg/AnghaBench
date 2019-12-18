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
struct exynos_drm_crtc {scalar_t__ i80_mode; struct decon_context* ctx; } ;
struct decon_context {int out_type; int /*<<< orphan*/  te_irq; int /*<<< orphan*/  irq; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ DECON_VIDINTCON0 ; 
 int I80_HW_TRG ; 
 int VIDINTCON0_FRAMEDONE ; 
 int VIDINTCON0_FRAMESEL_FP ; 
 int VIDINTCON0_INTEN ; 
 int VIDINTCON0_INTFRMEN ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int decon_enable_vblank(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	u32 val;

	val = VIDINTCON0_INTEN;
	if (crtc->i80_mode)
		val |= VIDINTCON0_FRAMEDONE;
	else
		val |= VIDINTCON0_INTFRMEN | VIDINTCON0_FRAMESEL_FP;

	writel(val, ctx->addr + DECON_VIDINTCON0);

	enable_irq(ctx->irq);
	if (!(ctx->out_type & I80_HW_TRG))
		enable_irq(ctx->te_irq);

	return 0;
}