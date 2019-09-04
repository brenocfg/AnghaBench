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
typedef  scalar_t__ u32 ;
struct xilinx_dma_chan {scalar_t__ desc_offset; TYPE_1__* xdev; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vdma_desc_write_64(struct xilinx_dma_chan *chan, u32 reg,
				      u32 value_lsb, u32 value_msb)
{
	/* Write the lsb 32 bits*/
	writel(value_lsb, chan->xdev->regs + chan->desc_offset + reg);

	/* Write the msb 32 bits */
	writel(value_msb, chan->xdev->regs + chan->desc_offset + reg + 4);
}