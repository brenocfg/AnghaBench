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
struct zynqmp_dma_desc_ll {int ctrl; } ;
struct zynqmp_dma_chan {int dummy; } ;

/* Variables and functions */
 int ZYNQMP_DMA_DESC_CTRL_COMP_INT ; 
 int ZYNQMP_DMA_DESC_CTRL_STOP ; 

__attribute__((used)) static void zynqmp_dma_desc_config_eod(struct zynqmp_dma_chan *chan,
				       void *desc)
{
	struct zynqmp_dma_desc_ll *hw = (struct zynqmp_dma_desc_ll *)desc;

	hw->ctrl |= ZYNQMP_DMA_DESC_CTRL_STOP;
	hw++;
	hw->ctrl |= ZYNQMP_DMA_DESC_CTRL_COMP_INT | ZYNQMP_DMA_DESC_CTRL_STOP;
}