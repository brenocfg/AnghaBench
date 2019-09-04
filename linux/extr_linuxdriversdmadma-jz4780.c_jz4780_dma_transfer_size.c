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
typedef  int uint32_t ;

/* Variables and functions */
 int JZ_DMA_SIZE_128_BYTE ; 
 int JZ_DMA_SIZE_16_BYTE ; 
 int JZ_DMA_SIZE_1_BYTE ; 
 int JZ_DMA_SIZE_2_BYTE ; 
 int JZ_DMA_SIZE_32_BYTE ; 
 int JZ_DMA_SIZE_4_BYTE ; 
 int JZ_DMA_SIZE_64_BYTE ; 
 int ffs (unsigned long) ; 

__attribute__((used)) static uint32_t jz4780_dma_transfer_size(unsigned long val, uint32_t *shift)
{
	int ord = ffs(val) - 1;

	/*
	 * 8 byte transfer sizes unsupported so fall back on 4. If it's larger
	 * than the maximum, just limit it. It is perfectly safe to fall back
	 * in this way since we won't exceed the maximum burst size supported
	 * by the device, the only effect is reduced efficiency. This is better
	 * than refusing to perform the request at all.
	 */
	if (ord == 3)
		ord = 2;
	else if (ord > 7)
		ord = 7;

	*shift = ord;

	switch (ord) {
	case 0:
		return JZ_DMA_SIZE_1_BYTE;
	case 1:
		return JZ_DMA_SIZE_2_BYTE;
	case 2:
		return JZ_DMA_SIZE_4_BYTE;
	case 4:
		return JZ_DMA_SIZE_16_BYTE;
	case 5:
		return JZ_DMA_SIZE_32_BYTE;
	case 6:
		return JZ_DMA_SIZE_64_BYTE;
	default:
		return JZ_DMA_SIZE_128_BYTE;
	}
}