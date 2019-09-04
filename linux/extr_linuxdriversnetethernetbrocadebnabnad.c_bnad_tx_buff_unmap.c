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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct bnad_tx_unmap {int nvecs; int /*<<< orphan*/ * vectors; struct sk_buff* skb; } ;
struct bnad {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BFI_TX_MAX_VECTORS_PER_WI ; 
 int /*<<< orphan*/  BNA_QE_INDX_INC (size_t,size_t) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static u32
bnad_tx_buff_unmap(struct bnad *bnad,
			      struct bnad_tx_unmap *unmap_q,
			      u32 q_depth, u32 index)
{
	struct bnad_tx_unmap *unmap;
	struct sk_buff *skb;
	int vector, nvecs;

	unmap = &unmap_q[index];
	nvecs = unmap->nvecs;

	skb = unmap->skb;
	unmap->skb = NULL;
	unmap->nvecs = 0;
	dma_unmap_single(&bnad->pcidev->dev,
		dma_unmap_addr(&unmap->vectors[0], dma_addr),
		skb_headlen(skb), DMA_TO_DEVICE);
	dma_unmap_addr_set(&unmap->vectors[0], dma_addr, 0);
	nvecs--;

	vector = 0;
	while (nvecs) {
		vector++;
		if (vector == BFI_TX_MAX_VECTORS_PER_WI) {
			vector = 0;
			BNA_QE_INDX_INC(index, q_depth);
			unmap = &unmap_q[index];
		}

		dma_unmap_page(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vectors[vector], dma_addr),
			dma_unmap_len(&unmap->vectors[vector], dma_len),
			DMA_TO_DEVICE);
		dma_unmap_addr_set(&unmap->vectors[vector], dma_addr, 0);
		nvecs--;
	}

	BNA_QE_INDX_INC(index, q_depth);

	return index;
}