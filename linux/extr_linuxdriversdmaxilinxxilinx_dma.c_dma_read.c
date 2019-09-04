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
struct xilinx_dma_chan {TYPE_1__* xdev; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 dma_read(struct xilinx_dma_chan *chan, u32 reg)
{
	return ioread32(chan->xdev->regs + reg);
}