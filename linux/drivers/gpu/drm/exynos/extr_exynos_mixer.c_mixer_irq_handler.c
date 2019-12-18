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
struct mixer_context {int /*<<< orphan*/  reg_slock; TYPE_1__* crtc; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MXR_BIT_INTERLACE ; 
 int MXR_INT_CLEAR_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_STATUS ; 
 int MXR_INT_STATUS_VSYNC ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_is_synced (struct mixer_context*) ; 
 int mixer_reg_read (struct mixer_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mixer_irq_handler(int irq, void *arg)
{
	struct mixer_context *ctx = arg;
	u32 val;

	spin_lock(&ctx->reg_slock);

	/* read interrupt status for handling and clearing flags for VSYNC */
	val = mixer_reg_read(ctx, MXR_INT_STATUS);

	/* handling VSYNC */
	if (val & MXR_INT_STATUS_VSYNC) {
		/* vsync interrupt use different bit for read and clear */
		val |= MXR_INT_CLEAR_VSYNC;
		val &= ~MXR_INT_STATUS_VSYNC;

		/* interlace scan need to check shadow register */
		if (test_bit(MXR_BIT_INTERLACE, &ctx->flags)
		    && !mixer_is_synced(ctx))
			goto out;

		drm_crtc_handle_vblank(&ctx->crtc->base);
	}

out:
	/* clear interrupts */
	mixer_reg_write(ctx, MXR_INT_STATUS, val);

	spin_unlock(&ctx->reg_slock);

	return IRQ_HANDLED;
}