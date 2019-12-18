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
struct decon_context {int out_type; scalar_t__ addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  te_irq; } ;

/* Variables and functions */
 scalar_t__ DECON_VIDINTCON0 ; 
 int I80_HW_TRG ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decon_disable_vblank(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;

	if (!(ctx->out_type & I80_HW_TRG))
		disable_irq_nosync(ctx->te_irq);
	disable_irq_nosync(ctx->irq);

	writel(0, ctx->addr + DECON_VIDINTCON0);
}