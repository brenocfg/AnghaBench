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
 int XILINX_DMA_DMASR_IDLE ; 
 int /*<<< orphan*/  XILINX_DMA_LOOP_COUNT ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMASR ; 
 int xilinx_dma_poll_timeout (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilinx_cdma_stop_transfer(struct xilinx_dma_chan *chan)
{
	u32 val;

	return xilinx_dma_poll_timeout(chan, XILINX_DMA_REG_DMASR, val,
				       val & XILINX_DMA_DMASR_IDLE, 0,
				       XILINX_DMA_LOOP_COUNT);
}