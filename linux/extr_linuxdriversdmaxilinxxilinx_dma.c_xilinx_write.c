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
struct xilinx_dma_chan {scalar_t__ ext_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_ctrl_write (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writeq (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xilinx_write(struct xilinx_dma_chan *chan, u32 reg,
				dma_addr_t addr)
{
	if (chan->ext_addr)
		dma_writeq(chan, reg, addr);
	else
		dma_ctrl_write(chan, reg, addr);
}