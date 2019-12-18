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

/* Variables and functions */
#define  TW686X_DMA_MODE_CONTIG 130 
#define  TW686X_DMA_MODE_MEMCPY 129 
#define  TW686X_DMA_MODE_SG 128 

__attribute__((used)) static const char *dma_mode_name(unsigned int mode)
{
	switch (mode) {
	case TW686X_DMA_MODE_MEMCPY:
		return "memcpy";
	case TW686X_DMA_MODE_CONTIG:
		return "contig";
	case TW686X_DMA_MODE_SG:
		return "sg";
	default:
		return "unknown";
	}
}