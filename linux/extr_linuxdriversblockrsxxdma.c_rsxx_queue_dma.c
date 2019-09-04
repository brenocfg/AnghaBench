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
struct TYPE_2__ {unsigned int off; unsigned int cnt; } ;
struct rsxx_dma {unsigned int laddr; unsigned int pg_off; int /*<<< orphan*/  list; struct page* page; TYPE_1__ sub_page; void* cb_data; int /*<<< orphan*/  cb; int /*<<< orphan*/  cmd; } ;
struct rsxx_cardinfo {int dummy; } ;
struct page {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  rsxx_dma_cb ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_CMD_BLK_READ ; 
 int /*<<< orphan*/  HW_CMD_BLK_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,unsigned int,unsigned int,unsigned int,struct page*,unsigned int) ; 
 struct rsxx_dma* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  rsxx_dma_pool ; 

__attribute__((used)) static blk_status_t rsxx_queue_dma(struct rsxx_cardinfo *card,
			      struct list_head *q,
			      int dir,
			      unsigned int dma_off,
			      unsigned int dma_len,
			      unsigned int laddr,
			      struct page *page,
			      unsigned int pg_off,
			      rsxx_dma_cb cb,
			      void *cb_data)
{
	struct rsxx_dma *dma;

	dma = kmem_cache_alloc(rsxx_dma_pool, GFP_KERNEL);
	if (!dma)
		return BLK_STS_RESOURCE;

	dma->cmd          = dir ? HW_CMD_BLK_WRITE : HW_CMD_BLK_READ;
	dma->laddr        = laddr;
	dma->sub_page.off = (dma_off >> 9);
	dma->sub_page.cnt = (dma_len >> 9);
	dma->page         = page;
	dma->pg_off       = pg_off;
	dma->cb	          = cb;
	dma->cb_data      = cb_data;

	dev_dbg(CARD_TO_DEV(card),
		"Queuing[%c] laddr %x off %d cnt %d page %p pg_off %d\n",
		dir ? 'W' : 'R', dma->laddr, dma->sub_page.off,
		dma->sub_page.cnt, dma->page, dma->pg_off);

	/* Queue the DMA */
	list_add_tail(&dma->list, q);

	return 0;
}