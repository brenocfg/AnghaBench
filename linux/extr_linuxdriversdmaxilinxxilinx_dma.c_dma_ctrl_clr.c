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
struct xilinx_dma_chan {int dummy; } ;

/* Variables and functions */
 int dma_ctrl_read (struct xilinx_dma_chan*,int) ; 
 int /*<<< orphan*/  dma_ctrl_write (struct xilinx_dma_chan*,int,int) ; 

__attribute__((used)) static inline void dma_ctrl_clr(struct xilinx_dma_chan *chan, u32 reg,
				 u32 clr)
{
	dma_ctrl_write(chan, reg, dma_ctrl_read(chan, reg) & ~clr);
}