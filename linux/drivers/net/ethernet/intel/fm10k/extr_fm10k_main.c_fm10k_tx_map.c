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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct sk_buff {unsigned char* data; unsigned int data_len; } ;
struct fm10k_tx_desc {scalar_t__ vlan; } ;
struct fm10k_tx_buffer {struct fm10k_tx_desc* next_to_watch; struct sk_buff* skb; int /*<<< orphan*/  bytecount; int /*<<< orphan*/  tx_flags; } ;
struct fm10k_ring {size_t next_to_use; size_t count; struct fm10k_tx_buffer* tx_buffer; int /*<<< orphan*/  dev; int /*<<< orphan*/  tail; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  unsigned int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int FM10K_MAX_DATA_PER_TXD ; 
 int /*<<< orphan*/  FM10K_TXD_FLAG_LAST ; 
 struct fm10k_tx_desc* FM10K_TX_DESC (struct fm10k_ring*,size_t) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ ,unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct fm10k_tx_buffer*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct fm10k_tx_buffer*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  fm10k_maybe_stop_tx (struct fm10k_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_tx_desc_flags (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_tx_desc_push (struct fm10k_ring*,struct fm10k_tx_desc*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_unmap_and_free_tx_resource (struct fm10k_ring*,struct fm10k_tx_buffer*) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  txring_txq (struct fm10k_ring*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_tx_map(struct fm10k_ring *tx_ring,
			 struct fm10k_tx_buffer *first)
{
	struct sk_buff *skb = first->skb;
	struct fm10k_tx_buffer *tx_buffer;
	struct fm10k_tx_desc *tx_desc;
	skb_frag_t *frag;
	unsigned char *data;
	dma_addr_t dma;
	unsigned int data_len, size;
	u32 tx_flags = first->tx_flags;
	u16 i = tx_ring->next_to_use;
	u8 flags = fm10k_tx_desc_flags(skb, tx_flags);

	tx_desc = FM10K_TX_DESC(tx_ring, i);

	/* add HW VLAN tag */
	if (skb_vlan_tag_present(skb))
		tx_desc->vlan = cpu_to_le16(skb_vlan_tag_get(skb));
	else
		tx_desc->vlan = 0;

	size = skb_headlen(skb);
	data = skb->data;

	dma = dma_map_single(tx_ring->dev, data, size, DMA_TO_DEVICE);

	data_len = skb->data_len;
	tx_buffer = first;

	for (frag = &skb_shinfo(skb)->frags[0];; frag++) {
		if (dma_mapping_error(tx_ring->dev, dma))
			goto dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		while (unlikely(size > FM10K_MAX_DATA_PER_TXD)) {
			if (fm10k_tx_desc_push(tx_ring, tx_desc++, i++, dma,
					       FM10K_MAX_DATA_PER_TXD, flags)) {
				tx_desc = FM10K_TX_DESC(tx_ring, 0);
				i = 0;
			}

			dma += FM10K_MAX_DATA_PER_TXD;
			size -= FM10K_MAX_DATA_PER_TXD;
		}

		if (likely(!data_len))
			break;

		if (fm10k_tx_desc_push(tx_ring, tx_desc++, i++,
				       dma, size, flags)) {
			tx_desc = FM10K_TX_DESC(tx_ring, 0);
			i = 0;
		}

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer[i];
	}

	/* write last descriptor with LAST bit set */
	flags |= FM10K_TXD_FLAG_LAST;

	if (fm10k_tx_desc_push(tx_ring, tx_desc, i++, dma, size, flags))
		i = 0;

	/* record bytecount for BQL */
	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* record SW timestamp if HW timestamp is not available */
	skb_tx_timestamp(first->skb);

	/* Force memory writes to complete before letting h/w know there
	 * are new descriptors to fetch.  (Only applicable for weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated before next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	tx_ring->next_to_use = i;

	/* Make sure there is space in the ring for the next send. */
	fm10k_maybe_stop_tx(tx_ring, DESC_NEEDED);

	/* notify HW of packet */
	if (netif_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) {
		writel(i, tx_ring->tail);
	}

	return;
dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings for failed tx_buffer map */
	for (;;) {
		tx_buffer = &tx_ring->tx_buffer[i];
		fm10k_unmap_and_free_tx_resource(tx_ring, tx_buffer);
		if (tx_buffer == first)
			break;
		if (i == 0)
			i = tx_ring->count;
		i--;
	}

	tx_ring->next_to_use = i;
}