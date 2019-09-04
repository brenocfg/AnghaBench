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
struct TYPE_2__ {int top; int left; } ;
struct flite_frame {int f_height; int f_width; TYPE_1__ rect; } ;
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FLITE_REG_CIOCAN ; 
 int FLITE_REG_CIOCAN_MASK ; 
 scalar_t__ FLITE_REG_CIOOFF ; 
 int FLITE_REG_CIOOFF_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void flite_hw_set_dma_window(struct fimc_lite *dev, struct flite_frame *f)
{
	u32 cfg;

	/* Maximum output pixel size */
	cfg = readl(dev->regs + FLITE_REG_CIOCAN);
	cfg &= ~FLITE_REG_CIOCAN_MASK;
	cfg |= (f->f_height << 16) | f->f_width;
	writel(cfg, dev->regs + FLITE_REG_CIOCAN);

	/* DMA offsets */
	cfg = readl(dev->regs + FLITE_REG_CIOOFF);
	cfg &= ~FLITE_REG_CIOOFF_MASK;
	cfg |= (f->rect.top << 16) | f->rect.left;
	writel(cfg, dev->regs + FLITE_REG_CIOOFF);
}