#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct e1000_rx_buffer {int /*<<< orphan*/  dma; } ;
struct e1000_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  copybreak ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* e1000_alloc_rx_skb (struct e1000_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *e1000_copybreak(struct e1000_adapter *adapter,
				       struct e1000_rx_buffer *buffer_info,
				       u32 length, const void *data)
{
	struct sk_buff *skb;

	if (length > copybreak)
		return NULL;

	skb = e1000_alloc_rx_skb(adapter, length);
	if (!skb)
		return NULL;

	dma_sync_single_for_cpu(&adapter->pdev->dev, buffer_info->dma,
				length, DMA_FROM_DEVICE);

	skb_put_data(skb, data, length);

	return skb;
}