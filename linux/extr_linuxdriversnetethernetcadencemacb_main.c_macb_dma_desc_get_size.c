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
struct macb_dma_desc {int dummy; } ;
struct macb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int macb_dma_desc_get_size(struct macb *bp)
{
#ifdef MACB_EXT_DESC
	unsigned int desc_size;

	switch (bp->hw_dma_cap) {
	case HW_DMA_CAP_64B:
		desc_size = sizeof(struct macb_dma_desc)
			+ sizeof(struct macb_dma_desc_64);
		break;
	case HW_DMA_CAP_PTP:
		desc_size = sizeof(struct macb_dma_desc)
			+ sizeof(struct macb_dma_desc_ptp);
		break;
	case HW_DMA_CAP_64B_PTP:
		desc_size = sizeof(struct macb_dma_desc)
			+ sizeof(struct macb_dma_desc_64)
			+ sizeof(struct macb_dma_desc_ptp);
		break;
	default:
		desc_size = sizeof(struct macb_dma_desc);
	}
	return desc_size;
#endif
	return sizeof(struct macb_dma_desc);
}