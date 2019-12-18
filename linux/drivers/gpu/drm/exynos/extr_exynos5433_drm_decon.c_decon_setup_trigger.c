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
struct decon_context {int out_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  sysreg; scalar_t__ addr; TYPE_1__* crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  i80_mode; } ;

/* Variables and functions */
 scalar_t__ DECON_TRIGCON ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DSD_CFG_MUX ; 
 int /*<<< orphan*/  DSD_CFG_MUX_TE_UNMASK_GLOBAL ; 
 int I80_HW_TRG ; 
 int TRIGCON_HWTRIGEN ; 
 int TRIGCON_HWTRIGMASK ; 
 int TRIGCON_SWTRIGEN ; 
 int TRIGCON_TE_AUTO_MASK ; 
 int TRIGCON_TRIGEN_F ; 
 int TRIGCON_TRIGEN_PER_F ; 
 scalar_t__ regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void decon_setup_trigger(struct decon_context *ctx)
{
	if (!ctx->crtc->i80_mode && !(ctx->out_type & I80_HW_TRG))
		return;

	if (!(ctx->out_type & I80_HW_TRG)) {
		writel(TRIGCON_TRIGEN_PER_F | TRIGCON_TRIGEN_F |
		       TRIGCON_TE_AUTO_MASK | TRIGCON_SWTRIGEN,
		       ctx->addr + DECON_TRIGCON);
		return;
	}

	writel(TRIGCON_TRIGEN_PER_F | TRIGCON_TRIGEN_F | TRIGCON_HWTRIGMASK
	       | TRIGCON_HWTRIGEN, ctx->addr + DECON_TRIGCON);

	if (regmap_update_bits(ctx->sysreg, DSD_CFG_MUX,
			       DSD_CFG_MUX_TE_UNMASK_GLOBAL, ~0))
		DRM_DEV_ERROR(ctx->dev, "Cannot update sysreg.\n");
}