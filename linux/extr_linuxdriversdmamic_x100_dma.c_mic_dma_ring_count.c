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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MIC_DMA_DESC_RX_SIZE ; 

__attribute__((used)) static u32 mic_dma_ring_count(u32 head, u32 tail)
{
	u32 count;

	if (head >= tail)
		count = (tail - 0) + (MIC_DMA_DESC_RX_SIZE - head);
	else
		count = tail - head;
	return count - 1;
}