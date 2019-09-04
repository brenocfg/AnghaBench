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
struct stm32_dma_chan {int dummy; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 int EINVAL ; 
 int STM32_DMA_BYTE ; 
 int STM32_DMA_HALF_WORD ; 
 int STM32_DMA_WORD ; 
 int /*<<< orphan*/  chan2dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stm32_dma_get_width(struct stm32_dma_chan *chan,
			       enum dma_slave_buswidth width)
{
	switch (width) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		return STM32_DMA_BYTE;
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		return STM32_DMA_HALF_WORD;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		return STM32_DMA_WORD;
	default:
		dev_err(chan2dev(chan), "Dma bus width not supported\n");
		return -EINVAL;
	}
}