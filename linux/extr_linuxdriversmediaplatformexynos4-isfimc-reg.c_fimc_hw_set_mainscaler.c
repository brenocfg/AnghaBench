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
struct fimc_variant {scalar_t__ has_mainscaler_ext; } ;
struct fimc_scaler {int /*<<< orphan*/  main_vratio; int /*<<< orphan*/  main_hratio; } ;
struct fimc_dev {scalar_t__ regs; struct fimc_variant* variant; } ;
struct fimc_ctx {struct fimc_scaler scaler; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIEXTEN ; 
 int FIMC_REG_CIEXTEN_MHRATIO_EXT (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CIEXTEN_MHRATIO_EXT_MASK ; 
 int FIMC_REG_CIEXTEN_MVRATIO_EXT (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CIEXTEN_MVRATIO_EXT_MASK ; 
 scalar_t__ FIMC_REG_CISCCTRL ; 
 int FIMC_REG_CISCCTRL_MHRATIO (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CISCCTRL_MHRATIO_EXT (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CISCCTRL_MHRATIO_MASK ; 
 int FIMC_REG_CISCCTRL_MVRATIO (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CISCCTRL_MVRATIO_EXT (int /*<<< orphan*/ ) ; 
 int FIMC_REG_CISCCTRL_MVRATIO_MASK ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_hw_set_scaler (struct fimc_ctx*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fimc_hw_set_mainscaler(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	const struct fimc_variant *variant = dev->variant;
	struct fimc_scaler *sc = &ctx->scaler;
	u32 cfg;

	dbg("main_hratio= 0x%X  main_vratio= 0x%X",
	    sc->main_hratio, sc->main_vratio);

	fimc_hw_set_scaler(ctx);

	cfg = readl(dev->regs + FIMC_REG_CISCCTRL);
	cfg &= ~(FIMC_REG_CISCCTRL_MHRATIO_MASK |
		 FIMC_REG_CISCCTRL_MVRATIO_MASK);

	if (variant->has_mainscaler_ext) {
		cfg |= FIMC_REG_CISCCTRL_MHRATIO_EXT(sc->main_hratio);
		cfg |= FIMC_REG_CISCCTRL_MVRATIO_EXT(sc->main_vratio);
		writel(cfg, dev->regs + FIMC_REG_CISCCTRL);

		cfg = readl(dev->regs + FIMC_REG_CIEXTEN);

		cfg &= ~(FIMC_REG_CIEXTEN_MVRATIO_EXT_MASK |
			 FIMC_REG_CIEXTEN_MHRATIO_EXT_MASK);
		cfg |= FIMC_REG_CIEXTEN_MHRATIO_EXT(sc->main_hratio);
		cfg |= FIMC_REG_CIEXTEN_MVRATIO_EXT(sc->main_vratio);
		writel(cfg, dev->regs + FIMC_REG_CIEXTEN);
	} else {
		cfg |= FIMC_REG_CISCCTRL_MHRATIO(sc->main_hratio);
		cfg |= FIMC_REG_CISCCTRL_MVRATIO(sc->main_vratio);
		writel(cfg, dev->regs + FIMC_REG_CISCCTRL);
	}
}