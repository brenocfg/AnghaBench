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
struct TYPE_3__ {void* cmd_type_len; scalar_t__ olinfo_status; void* buffer_addr; } ;
union ixgbe_adv_tx_desc {TYPE_1__ read; } ;
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
typedef  size_t u16 ;
struct skb_frag_struct {int dummy; } ;
struct sk_buff {unsigned int data_len; int /*<<< orphan*/  xmit_more; int /*<<< orphan*/  data; scalar_t__ const len; } ;
struct ixgbe_tx_buffer {unsigned int tx_flags; struct sk_buff* skb; union ixgbe_adv_tx_desc* next_to_watch; int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  bytecount; } ;
struct ixgbe_ring {size_t next_to_use; size_t count; int /*<<< orphan*/  dev; struct ixgbe_tx_buffer* tx_buffer_info; int /*<<< orphan*/  tail; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_4__ {struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int IXGBE_MAX_DATA_PER_TXD ; 
 unsigned int IXGBE_TXD_CMD ; 
 union ixgbe_adv_tx_desc* IXGBE_TX_DESC (struct ixgbe_ring*,size_t) ; 
 void* cpu_to_le32 (unsigned int) ; 
 void* cpu_to_le64 (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ixgbe_tx_buffer*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct ixgbe_tx_buffer*,unsigned int,unsigned int) ; 
 scalar_t__ dma_unmap_len (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_maybe_stop_tx (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 unsigned int ixgbe_tx_cmd_type (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ixgbe_tx_olinfo_status (union ixgbe_adv_tx_desc*,unsigned int,scalar_t__ const) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_dma_map (int /*<<< orphan*/ ,struct skb_frag_struct*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (struct skb_frag_struct*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  txring_txq (struct ixgbe_ring*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_tx_map(struct ixgbe_ring *tx_ring,
			struct ixgbe_tx_buffer *first,
			const u8 hdr_len)
{
	struct sk_buff *skb = first->skb;
	struct ixgbe_tx_buffer *tx_buffer;
	union ixgbe_adv_tx_desc *tx_desc;
	struct skb_frag_struct *frag;
	dma_addr_t dma;
	unsigned int data_len, size;
	u32 tx_flags = first->tx_flags;
	u32 cmd_type = ixgbe_tx_cmd_type(skb, tx_flags);
	u16 i = tx_ring->next_to_use;

	tx_desc = IXGBE_TX_DESC(tx_ring, i);

	ixgbe_tx_olinfo_status(tx_desc, tx_flags, skb->len - hdr_len);

	size = skb_headlen(skb);
	data_len = skb->data_len;

#ifdef IXGBE_FCOE
	if (tx_flags & IXGBE_TX_FLAGS_FCOE) {
		if (data_len < sizeof(struct fcoe_crc_eof)) {
			size -= sizeof(struct fcoe_crc_eof) - data_len;
			data_len = 0;
		} else {
			data_len -= sizeof(struct fcoe_crc_eof);
		}
	}

#endif
	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffer = first;

	for (frag = &skb_shinfo(skb)->frags[0];; frag++) {
		if (dma_mapping_error(tx_ring->dev, dma))
			goto dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		tx_desc->read.buffer_addr = cpu_to_le64(dma);

		while (unlikely(size > IXGBE_MAX_DATA_PER_TXD)) {
			tx_desc->read.cmd_type_len =
				cpu_to_le32(cmd_type ^ IXGBE_MAX_DATA_PER_TXD);

			i++;
			tx_desc++;
			if (i == tx_ring->count) {
				tx_desc = IXGBE_TX_DESC(tx_ring, 0);
				i = 0;
			}
			tx_desc->read.olinfo_status = 0;

			dma += IXGBE_MAX_DATA_PER_TXD;
			size -= IXGBE_MAX_DATA_PER_TXD;

			tx_desc->read.buffer_addr = cpu_to_le64(dma);
		}

		if (likely(!data_len))
			break;

		tx_desc->read.cmd_type_len = cpu_to_le32(cmd_type ^ size);

		i++;
		tx_desc++;
		if (i == tx_ring->count) {
			tx_desc = IXGBE_TX_DESC(tx_ring, 0);
			i = 0;
		}
		tx_desc->read.olinfo_status = 0;

#ifdef IXGBE_FCOE
		size = min_t(unsigned int, data_len, skb_frag_size(frag));
#else
		size = skb_frag_size(frag);
#endif
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer_info[i];
	}

	/* write last descriptor with RS and EOP bits */
	cmd_type |= size | IXGBE_TXD_CMD;
	tx_desc->read.cmd_type_len = cpu_to_le32(cmd_type);

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* set the timestamp */
	first->time_stamp = jiffies;

	/*
	 * Force memory writes to complete before letting h/w know there
	 * are new descriptors to fetch.  (Only applicable for weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated before next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	i++;
	if (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	ixgbe_maybe_stop_tx(tx_ring, DESC_NEEDED);

	if (netif_xmit_stopped(txring_txq(tx_ring)) || !skb->xmit_more) {
		writel(i, tx_ring->tail);

		/* we need this if more than one processor can write to our tail
		 * at a time, it synchronizes IO on IA64/Altix systems
		 */
		mmiowb();
	}

	return 0;
dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings for failed tx_buffer_info map */
	for (;;) {
		tx_buffer = &tx_ring->tx_buffer_info[i];
		if (dma_unmap_len(tx_buffer, len))
			dma_unmap_page(tx_ring->dev,
				       dma_unmap_addr(tx_buffer, dma),
				       dma_unmap_len(tx_buffer, len),
				       DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);
		if (tx_buffer == first)
			break;
		if (i == 0)
			i += tx_ring->count;
		i--;
	}

	dev_kfree_skb_any(first->skb);
	first->skb = NULL;

	tx_ring->next_to_use = i;

	return -1;
}