#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct skb_frame_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  skb_dma; } ;
struct queue_entry {TYPE_3__* skb; TYPE_2__* queue; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__* rt2x00dev; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SKBDESC_DMA_MAPPED_TX ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_3__*) ; 
 int /*<<< orphan*/  rt2x00lib_dmadone (struct queue_entry*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int rt2x00queue_map_txskb(struct queue_entry *entry)
{
	struct device *dev = entry->queue->rt2x00dev->dev;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);

	skbdesc->skb_dma =
	    dma_map_single(dev, entry->skb->data, entry->skb->len, DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(dev, skbdesc->skb_dma)))
		return -ENOMEM;

	skbdesc->flags |= SKBDESC_DMA_MAPPED_TX;
	rt2x00lib_dmadone(entry);
	return 0;
}