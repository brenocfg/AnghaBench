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

/* Variables and functions */
#define  STM32_DMA_FIFO_THRESHOLD_FULL 129 
#define  STM32_DMA_FIFO_THRESHOLD_HALFFULL 128 
 int STM32_DMA_MAX_BURST ; 

__attribute__((used)) static bool stm32_dma_is_burst_possible(u32 buf_len, u32 threshold)
{
	switch (threshold) {
	case STM32_DMA_FIFO_THRESHOLD_FULL:
		if (buf_len >= STM32_DMA_MAX_BURST)
			return true;
		else
			return false;
	case STM32_DMA_FIFO_THRESHOLD_HALFFULL:
		if (buf_len >= STM32_DMA_MAX_BURST / 2)
			return true;
		else
			return false;
	default:
		return false;
	}
}