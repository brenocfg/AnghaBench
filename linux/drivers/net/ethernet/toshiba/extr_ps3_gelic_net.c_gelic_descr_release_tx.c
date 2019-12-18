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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct gelic_descr {struct sk_buff* skb; scalar_t__ data_error; scalar_t__ data_status; scalar_t__ valid_size; scalar_t__ result_size; scalar_t__ next_descr_addr; scalar_t__ buf_size; scalar_t__ buf_addr; } ;
struct gelic_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GELIC_DESCR_DMA_NOT_IN_USE ; 
 int GELIC_DESCR_TX_TAIL ; 
 int be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_descr_set_status (struct gelic_descr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_descr_release_tx(struct gelic_card *card,
				       struct gelic_descr *descr)
{
	struct sk_buff *skb = descr->skb;

	BUG_ON(!(be32_to_cpu(descr->data_status) & GELIC_DESCR_TX_TAIL));

	dma_unmap_single(ctodev(card), be32_to_cpu(descr->buf_addr), skb->len,
			 DMA_TO_DEVICE);
	dev_kfree_skb_any(skb);

	descr->buf_addr = 0;
	descr->buf_size = 0;
	descr->next_descr_addr = 0;
	descr->result_size = 0;
	descr->valid_size = 0;
	descr->data_status = 0;
	descr->data_error = 0;
	descr->skb = NULL;

	/* set descr status */
	gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);
}