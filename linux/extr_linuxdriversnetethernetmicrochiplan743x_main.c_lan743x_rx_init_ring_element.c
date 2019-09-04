#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct lan743x_rx_descriptor {int data0; scalar_t__ data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;
struct lan743x_rx_buffer_info {int buffer_length; struct sk_buff* skb; scalar_t__ dma_ptr; } ;
struct lan743x_rx {TYPE_2__* adapter; struct lan743x_rx_buffer_info* buffer_info; struct lan743x_rx_descriptor* ring_cpu_ptr; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_HIGH32 (scalar_t__) ; 
 int /*<<< orphan*/  DMA_ADDR_LOW32 (scalar_t__) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int ETH_HLEN ; 
 int LAN743X_MAX_FRAME_SIZE ; 
 int RX_DESC_DATA0_BUF_LENGTH_MASK_ ; 
 int RX_DESC_DATA0_OWN_ ; 
 int RX_HEAD_PADDING ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int lan743x_rx_init_ring_element(struct lan743x_rx *rx, int index,
					struct sk_buff *skb)
{
	struct lan743x_rx_buffer_info *buffer_info;
	struct lan743x_rx_descriptor *descriptor;
	int length = 0;

	length = (LAN743X_MAX_FRAME_SIZE + ETH_HLEN + 4 + RX_HEAD_PADDING);
	descriptor = &rx->ring_cpu_ptr[index];
	buffer_info = &rx->buffer_info[index];
	buffer_info->skb = skb;
	if (!(buffer_info->skb))
		return -ENOMEM;
	buffer_info->dma_ptr = dma_map_single(&rx->adapter->pdev->dev,
					      buffer_info->skb->data,
					      length,
					      DMA_FROM_DEVICE);
	if (dma_mapping_error(&rx->adapter->pdev->dev,
			      buffer_info->dma_ptr)) {
		buffer_info->dma_ptr = 0;
		return -ENOMEM;
	}

	buffer_info->buffer_length = length;
	descriptor->data1 = DMA_ADDR_LOW32(buffer_info->dma_ptr);
	descriptor->data2 = DMA_ADDR_HIGH32(buffer_info->dma_ptr);
	descriptor->data3 = 0;
	descriptor->data0 = (RX_DESC_DATA0_OWN_ |
			    (length & RX_DESC_DATA0_BUF_LENGTH_MASK_));
	skb_reserve(buffer_info->skb, RX_HEAD_PADDING);

	return 0;
}