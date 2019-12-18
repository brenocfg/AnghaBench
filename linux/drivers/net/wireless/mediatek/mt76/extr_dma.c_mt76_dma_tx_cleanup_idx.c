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
typedef  int u32 ;
struct mt76_queue_entry {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * txwi; int /*<<< orphan*/  skip_buf0; } ;
struct mt76_queue {TYPE_1__* desc; struct mt76_queue_entry* entry; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  buf1; int /*<<< orphan*/  buf0; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DMA_DUMMY_DATA ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int MT_DMA_CTL_LAST_SEC0 ; 
 int /*<<< orphan*/  MT_DMA_CTL_SD_LEN0 ; 
 int /*<<< orphan*/  MT_DMA_CTL_SD_LEN1 ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mt76_queue_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76_dma_tx_cleanup_idx(struct mt76_dev *dev, struct mt76_queue *q, int idx,
			struct mt76_queue_entry *prev_e)
{
	struct mt76_queue_entry *e = &q->entry[idx];
	__le32 __ctrl = READ_ONCE(q->desc[idx].ctrl);
	u32 ctrl = le32_to_cpu(__ctrl);

	if (!e->skip_buf0) {
		__le32 addr = READ_ONCE(q->desc[idx].buf0);
		u32 len = FIELD_GET(MT_DMA_CTL_SD_LEN0, ctrl);

		dma_unmap_single(dev->dev, le32_to_cpu(addr), len,
				 DMA_TO_DEVICE);
	}

	if (!(ctrl & MT_DMA_CTL_LAST_SEC0)) {
		__le32 addr = READ_ONCE(q->desc[idx].buf1);
		u32 len = FIELD_GET(MT_DMA_CTL_SD_LEN1, ctrl);

		dma_unmap_single(dev->dev, le32_to_cpu(addr), len,
				 DMA_TO_DEVICE);
	}

	if (e->txwi == DMA_DUMMY_DATA)
		e->txwi = NULL;

	if (e->skb == DMA_DUMMY_DATA)
		e->skb = NULL;

	*prev_e = *e;
	memset(e, 0, sizeof(*e));
}