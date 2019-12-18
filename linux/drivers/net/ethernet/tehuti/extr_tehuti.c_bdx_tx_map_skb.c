#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct txdb {TYPE_2__* wptr; } ;
struct txd_desc {struct pbl* pbl; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pbl {void* pa_hi; void* pa_lo; void* len; } ;
struct bdx_priv {TYPE_5__* pdev; struct txdb txdb; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_8__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_6__ {struct sk_buff* skb; int /*<<< orphan*/  dma; } ;
struct TYPE_7__ {TYPE_1__ addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 void* CPU_CHIP_SWAP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*,void*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  H32_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L32_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  bdx_tx_db_inc_wptr (struct txdb*) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 TYPE_3__* txd_sizes ; 

__attribute__((used)) static inline void
bdx_tx_map_skb(struct bdx_priv *priv, struct sk_buff *skb,
	       struct txd_desc *txdd)
{
	struct txdb *db = &priv->txdb;
	struct pbl *pbl = &txdd->pbl[0];
	int nr_frags = skb_shinfo(skb)->nr_frags;
	int i;

	db->wptr->len = skb_headlen(skb);
	db->wptr->addr.dma = pci_map_single(priv->pdev, skb->data,
					    db->wptr->len, PCI_DMA_TODEVICE);
	pbl->len = CPU_CHIP_SWAP32(db->wptr->len);
	pbl->pa_lo = CPU_CHIP_SWAP32(L32_64(db->wptr->addr.dma));
	pbl->pa_hi = CPU_CHIP_SWAP32(H32_64(db->wptr->addr.dma));
	DBG("=== pbl   len: 0x%x ================\n", pbl->len);
	DBG("=== pbl pa_lo: 0x%x ================\n", pbl->pa_lo);
	DBG("=== pbl pa_hi: 0x%x ================\n", pbl->pa_hi);
	bdx_tx_db_inc_wptr(db);

	for (i = 0; i < nr_frags; i++) {
		const skb_frag_t *frag;

		frag = &skb_shinfo(skb)->frags[i];
		db->wptr->len = skb_frag_size(frag);
		db->wptr->addr.dma = skb_frag_dma_map(&priv->pdev->dev, frag,
						      0, skb_frag_size(frag),
						      DMA_TO_DEVICE);

		pbl++;
		pbl->len = CPU_CHIP_SWAP32(db->wptr->len);
		pbl->pa_lo = CPU_CHIP_SWAP32(L32_64(db->wptr->addr.dma));
		pbl->pa_hi = CPU_CHIP_SWAP32(H32_64(db->wptr->addr.dma));
		bdx_tx_db_inc_wptr(db);
	}

	/* add skb clean up info. */
	db->wptr->len = -txd_sizes[nr_frags].bytes;
	db->wptr->addr.skb = skb;
	bdx_tx_db_inc_wptr(db);
}