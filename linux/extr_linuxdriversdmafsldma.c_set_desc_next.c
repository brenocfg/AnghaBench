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
typedef  int u64 ;
struct fsldma_chan {int feature; } ;
struct fsl_dma_ld_hw {int /*<<< orphan*/  next_ln_addr; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_DMA (struct fsldma_chan*,int,int) ; 
 int FSL_DMA_IP_83XX ; 
 int FSL_DMA_IP_MASK ; 
 int FSL_DMA_SNEN ; 

__attribute__((used)) static void set_desc_next(struct fsldma_chan *chan,
			  struct fsl_dma_ld_hw *hw, dma_addr_t next)
{
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_83XX)
		? FSL_DMA_SNEN : 0;
	hw->next_ln_addr = CPU_TO_DMA(chan, snoop_bits | next, 64);
}