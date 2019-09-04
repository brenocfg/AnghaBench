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
typedef  int /*<<< orphan*/  u8 ;
struct macb_dma_desc_ptp {int dummy; } ;
struct macb_dma_desc_64 {int dummy; } ;
struct macb_dma_desc {int dummy; } ;
struct macb {scalar_t__ hw_dma_cap; } ;

/* Variables and functions */
 scalar_t__ HW_DMA_CAP_64B_PTP ; 
 scalar_t__ HW_DMA_CAP_PTP ; 

__attribute__((used)) static struct macb_dma_desc_ptp *macb_ptp_desc(struct macb *bp,
					       struct macb_dma_desc *desc)
{
	if (bp->hw_dma_cap == HW_DMA_CAP_PTP)
		return (struct macb_dma_desc_ptp *)
				((u8 *)desc + sizeof(struct macb_dma_desc));
	if (bp->hw_dma_cap == HW_DMA_CAP_64B_PTP)
		return (struct macb_dma_desc_ptp *)
				((u8 *)desc + sizeof(struct macb_dma_desc)
				+ sizeof(struct macb_dma_desc_64));
	return NULL;
}