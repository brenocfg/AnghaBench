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
struct macb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int macb_adj_dma_desc_idx(struct macb *bp, unsigned int desc_idx)
{
#ifdef MACB_EXT_DESC
	switch (bp->hw_dma_cap) {
	case HW_DMA_CAP_64B:
	case HW_DMA_CAP_PTP:
		desc_idx <<= 1;
		break;
	case HW_DMA_CAP_64B_PTP:
		desc_idx *= 3;
		break;
	default:
		break;
	}
#endif
	return desc_idx;
}