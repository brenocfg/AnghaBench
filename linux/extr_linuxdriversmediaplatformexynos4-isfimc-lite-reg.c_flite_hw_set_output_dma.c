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
struct flite_frame {int dummy; } ;
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FLITE_REG_CIGCTRL ; 
 int /*<<< orphan*/  FLITE_REG_CIGCTRL_ODMA_DISABLE ; 
 int /*<<< orphan*/  flite_hw_set_dma_window (struct fimc_lite*,struct flite_frame*) ; 
 int /*<<< orphan*/  flite_hw_set_out_order (struct fimc_lite*,struct flite_frame*) ; 
 int /*<<< orphan*/  flite_hw_set_pack12 (struct fimc_lite*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void flite_hw_set_output_dma(struct fimc_lite *dev, struct flite_frame *f,
			     bool enable)
{
	u32 cfg = readl(dev->regs + FLITE_REG_CIGCTRL);

	if (!enable) {
		cfg |= FLITE_REG_CIGCTRL_ODMA_DISABLE;
		writel(cfg, dev->regs + FLITE_REG_CIGCTRL);
		return;
	}

	cfg &= ~FLITE_REG_CIGCTRL_ODMA_DISABLE;
	writel(cfg, dev->regs + FLITE_REG_CIGCTRL);

	flite_hw_set_out_order(dev, f);
	flite_hw_set_dma_window(dev, f);
	flite_hw_set_pack12(dev, 0);
}