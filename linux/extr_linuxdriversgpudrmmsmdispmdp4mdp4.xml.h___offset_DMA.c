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
typedef  enum mdp4_dma { ____Placeholder_mdp4_dma } mdp4_dma ;

/* Variables and functions */
#define  DMA_E 130 
#define  DMA_P 129 
#define  DMA_S 128 
 int INVALID_IDX (int) ; 

__attribute__((used)) static inline uint32_t __offset_DMA(enum mdp4_dma idx)
{
	switch (idx) {
		case DMA_P: return 0x00090000;
		case DMA_S: return 0x000a0000;
		case DMA_E: return 0x000b0000;
		default: return INVALID_IDX(idx);
	}
}