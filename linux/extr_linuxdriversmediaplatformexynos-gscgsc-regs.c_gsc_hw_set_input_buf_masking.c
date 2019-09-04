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
struct gsc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GSC_IN_BASE_ADDR_CB_MASK ; 
 scalar_t__ GSC_IN_BASE_ADDR_CR_MASK ; 
 scalar_t__ GSC_IN_BASE_ADDR_Y_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void gsc_hw_set_input_buf_masking(struct gsc_dev *dev, u32 shift,
				bool enable)
{
	u32 cfg = readl(dev->regs + GSC_IN_BASE_ADDR_Y_MASK);
	u32 mask = 1 << shift;

	cfg &= ~mask;
	cfg |= enable << shift;

	writel(cfg, dev->regs + GSC_IN_BASE_ADDR_Y_MASK);
	writel(cfg, dev->regs + GSC_IN_BASE_ADDR_CB_MASK);
	writel(cfg, dev->regs + GSC_IN_BASE_ADDR_CR_MASK);
}