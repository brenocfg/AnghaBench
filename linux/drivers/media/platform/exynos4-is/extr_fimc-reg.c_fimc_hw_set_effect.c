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
struct fimc_effect {int type; int pat_cb; int pat_cr; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {struct fimc_effect effect; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIIMGEFF ; 
 int FIMC_REG_CIIMGEFF_FIN_ARBITRARY ; 
 int FIMC_REG_CIIMGEFF_FIN_BYPASS ; 
 int FIMC_REG_CIIMGEFF_IE_ENABLE ; 
 int FIMC_REG_CIIMGEFF_IE_SC_AFTER ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fimc_hw_set_effect(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_effect *effect = &ctx->effect;
	u32 cfg = 0;

	if (effect->type != FIMC_REG_CIIMGEFF_FIN_BYPASS) {
		cfg |= FIMC_REG_CIIMGEFF_IE_SC_AFTER |
			FIMC_REG_CIIMGEFF_IE_ENABLE;
		cfg |= effect->type;
		if (effect->type == FIMC_REG_CIIMGEFF_FIN_ARBITRARY)
			cfg |= (effect->pat_cb << 13) | effect->pat_cr;
	}

	writel(cfg, dev->regs + FIMC_REG_CIIMGEFF);
}