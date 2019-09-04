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
struct lan743x_rx_descriptor {int data0; scalar_t__ data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;
struct lan743x_rx_buffer_info {int buffer_length; int /*<<< orphan*/  dma_ptr; } ;
struct lan743x_rx {struct lan743x_rx_buffer_info* buffer_info; struct lan743x_rx_descriptor* ring_cpu_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_HIGH32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ADDR_LOW32 (int /*<<< orphan*/ ) ; 
 int RX_DESC_DATA0_BUF_LENGTH_MASK_ ; 
 int RX_DESC_DATA0_OWN_ ; 

__attribute__((used)) static void lan743x_rx_reuse_ring_element(struct lan743x_rx *rx, int index)
{
	struct lan743x_rx_buffer_info *buffer_info;
	struct lan743x_rx_descriptor *descriptor;

	descriptor = &rx->ring_cpu_ptr[index];
	buffer_info = &rx->buffer_info[index];

	descriptor->data1 = DMA_ADDR_LOW32(buffer_info->dma_ptr);
	descriptor->data2 = DMA_ADDR_HIGH32(buffer_info->dma_ptr);
	descriptor->data3 = 0;
	descriptor->data0 = (RX_DESC_DATA0_OWN_ |
			    ((buffer_info->buffer_length) &
			    RX_DESC_DATA0_BUF_LENGTH_MASK_));
}