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
typedef  int u32 ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct mtk_tx_ring {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  free_count; struct mtk_tx_dma* next_free; struct mtk_tx_dma* last_free; } ;
struct mtk_tx_dma {int txd1; int txd2; int txd3; int txd4; } ;
struct mtk_tx_buf {struct sk_buff* skb; int /*<<< orphan*/  flags; } ;
struct mtk_mac {int id; struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_1__* soc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int dma_addr_t ;
struct TYPE_4__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MT7628_TX_CTX_IDX0 ; 
 scalar_t__ MTK_DMA_DUMMY_DESC ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QTX_CTX_PTR ; 
 int /*<<< orphan*/  MTK_TX_DMA_BUF_LEN ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_FPORT0 ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_FPORT1 ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_PAGE0 ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_SINGLE0 ; 
 int NEXT_DESP_IDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TX_DMA_CHKSUM ; 
 int TX_DMA_DESP2_DEF ; 
 int TX_DMA_FPORT_SHIFT ; 
 int TX_DMA_INS_VLAN ; 
 int TX_DMA_LS0 ; 
 int TX_DMA_LS1 ; 
 int TX_DMA_OWNER_CPU ; 
 int TX_DMA_PLEN0 (unsigned int) ; 
 int TX_DMA_SWC ; 
 int TX_DMA_TSO ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mtk_tx_buf*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 struct mtk_tx_buf* mtk_desc_to_tx_buf (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 void* mtk_qdma_phys_to_virt (struct mtk_tx_ring*,int) ; 
 int /*<<< orphan*/  mtk_tx_unmap (struct mtk_eth*,struct mtk_tx_buf*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 struct mtk_tx_dma* qdma_to_pdma (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 int /*<<< orphan*/  setup_tx_buf (struct mtk_eth*,struct mtk_tx_buf*,struct mtk_tx_dma*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  txd_to_idx (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_tx_map(struct sk_buff *skb, struct net_device *dev,
		      int tx_num, struct mtk_tx_ring *ring, bool gso)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	struct mtk_tx_dma *itxd, *txd;
	struct mtk_tx_dma *itxd_pdma, *txd_pdma;
	struct mtk_tx_buf *itx_buf, *tx_buf;
	dma_addr_t mapped_addr;
	unsigned int nr_frags;
	int i, n_desc = 1;
	u32 txd4 = 0, fport;
	int k = 0;

	itxd = ring->next_free;
	itxd_pdma = qdma_to_pdma(ring, itxd);
	if (itxd == ring->last_free)
		return -ENOMEM;

	/* set the forward port */
	fport = (mac->id + 1) << TX_DMA_FPORT_SHIFT;
	txd4 |= fport;

	itx_buf = mtk_desc_to_tx_buf(ring, itxd);
	memset(itx_buf, 0, sizeof(*itx_buf));

	if (gso)
		txd4 |= TX_DMA_TSO;

	/* TX Checksum offload */
	if (skb->ip_summed == CHECKSUM_PARTIAL)
		txd4 |= TX_DMA_CHKSUM;

	/* VLAN header offload */
	if (skb_vlan_tag_present(skb))
		txd4 |= TX_DMA_INS_VLAN | skb_vlan_tag_get(skb);

	mapped_addr = dma_map_single(eth->dev, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(eth->dev, mapped_addr)))
		return -ENOMEM;

	WRITE_ONCE(itxd->txd1, mapped_addr);
	itx_buf->flags |= MTK_TX_FLAGS_SINGLE0;
	itx_buf->flags |= (!mac->id) ? MTK_TX_FLAGS_FPORT0 :
			  MTK_TX_FLAGS_FPORT1;
	setup_tx_buf(eth, itx_buf, itxd_pdma, mapped_addr, skb_headlen(skb),
		     k++);

	/* TX SG offload */
	txd = itxd;
	txd_pdma = qdma_to_pdma(ring, txd);
	nr_frags = skb_shinfo(skb)->nr_frags;

	for (i = 0; i < nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		unsigned int offset = 0;
		int frag_size = skb_frag_size(frag);

		while (frag_size) {
			bool last_frag = false;
			unsigned int frag_map_size;
			bool new_desc = true;

			if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA) ||
			    (i & 0x1)) {
				txd = mtk_qdma_phys_to_virt(ring, txd->txd2);
				txd_pdma = qdma_to_pdma(ring, txd);
				if (txd == ring->last_free)
					goto err_dma;

				n_desc++;
			} else {
				new_desc = false;
			}


			frag_map_size = min(frag_size, MTK_TX_DMA_BUF_LEN);
			mapped_addr = skb_frag_dma_map(eth->dev, frag, offset,
						       frag_map_size,
						       DMA_TO_DEVICE);
			if (unlikely(dma_mapping_error(eth->dev, mapped_addr)))
				goto err_dma;

			if (i == nr_frags - 1 &&
			    (frag_size - frag_map_size) == 0)
				last_frag = true;

			WRITE_ONCE(txd->txd1, mapped_addr);
			WRITE_ONCE(txd->txd3, (TX_DMA_SWC |
					       TX_DMA_PLEN0(frag_map_size) |
					       last_frag * TX_DMA_LS0));
			WRITE_ONCE(txd->txd4, fport);

			tx_buf = mtk_desc_to_tx_buf(ring, txd);
			if (new_desc)
				memset(tx_buf, 0, sizeof(*tx_buf));
			tx_buf->skb = (struct sk_buff *)MTK_DMA_DUMMY_DESC;
			tx_buf->flags |= MTK_TX_FLAGS_PAGE0;
			tx_buf->flags |= (!mac->id) ? MTK_TX_FLAGS_FPORT0 :
					 MTK_TX_FLAGS_FPORT1;

			setup_tx_buf(eth, tx_buf, txd_pdma, mapped_addr,
				     frag_map_size, k++);

			frag_size -= frag_map_size;
			offset += frag_map_size;
		}
	}

	/* store skb to cleanup */
	itx_buf->skb = skb;

	WRITE_ONCE(itxd->txd4, txd4);
	WRITE_ONCE(itxd->txd3, (TX_DMA_SWC | TX_DMA_PLEN0(skb_headlen(skb)) |
				(!nr_frags * TX_DMA_LS0)));
	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		if (k & 0x1)
			txd_pdma->txd2 |= TX_DMA_LS0;
		else
			txd_pdma->txd2 |= TX_DMA_LS1;
	}

	netdev_sent_queue(dev, skb->len);
	skb_tx_timestamp(skb);

	ring->next_free = mtk_qdma_phys_to_virt(ring, txd->txd2);
	atomic_sub(n_desc, &ring->free_count);

	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		if (netif_xmit_stopped(netdev_get_tx_queue(dev, 0)) ||
		    !netdev_xmit_more())
			mtk_w32(eth, txd->txd2, MTK_QTX_CTX_PTR);
	} else {
		int next_idx = NEXT_DESP_IDX(txd_to_idx(ring, txd),
					     ring->dma_size);
		mtk_w32(eth, next_idx, MT7628_TX_CTX_IDX0);
	}

	return 0;

err_dma:
	do {
		tx_buf = mtk_desc_to_tx_buf(ring, itxd);

		/* unmap dma */
		mtk_tx_unmap(eth, tx_buf);

		itxd->txd3 = TX_DMA_LS0 | TX_DMA_OWNER_CPU;
		if (!MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
			itxd_pdma->txd2 = TX_DMA_DESP2_DEF;

		itxd = mtk_qdma_phys_to_virt(ring, itxd->txd2);
		itxd_pdma = qdma_to_pdma(ring, itxd);
	} while (itxd != txd);

	return -ENOMEM;
}