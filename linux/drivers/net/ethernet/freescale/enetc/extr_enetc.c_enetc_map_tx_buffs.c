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
struct TYPE_3__ {int e_flags; scalar_t__ tpid; void* vid; } ;
union enetc_tx_bd {int flags; void* buf_len; void* addr; TYPE_1__ ext; void* frm_len; scalar_t__ lstatus; } ;
typedef  int u8 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct enetc_tx_swbd {int len; int is_dma_page; int do_tstamp; int check_wb; struct sk_buff* skb; void* dma; } ;
struct enetc_bdr {int next_to_use; int bd_count; struct enetc_tx_swbd* tx_swbd; int /*<<< orphan*/  dev; int /*<<< orphan*/  tpir; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {int tx_flags; unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENETC_F_TX_TSTAMP ; 
 union enetc_tx_bd* ENETC_TXBD (struct enetc_bdr,int) ; 
 int ENETC_TXBD_E_FLAGS_TWO_STEP_PTP ; 
 int ENETC_TXBD_E_FLAGS_VLAN_INS ; 
 int ENETC_TXBD_FLAGS_CSUM ; 
 int ENETC_TXBD_FLAGS_EX ; 
 int ENETC_TXBD_FLAGS_F ; 
 int ENETC_TXBD_FLAGS_L4CS ; 
 int SKBTX_HW_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le64 (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  enetc_bdr_idx_inc (struct enetc_bdr*,int*) ; 
 int /*<<< orphan*/  enetc_clear_tx_bd (union enetc_tx_bd*) ; 
 int /*<<< orphan*/  enetc_free_tx_skb (struct enetc_bdr*,struct enetc_tx_swbd*) ; 
 scalar_t__ enetc_tx_csum (struct sk_buff*,union enetc_tx_bd*) ; 
 int /*<<< orphan*/  enetc_wr_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefetchw (union enetc_tx_bd*) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 int skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int enetc_map_tx_buffs(struct enetc_bdr *tx_ring, struct sk_buff *skb,
			      int active_offloads)
{
	struct enetc_tx_swbd *tx_swbd;
	skb_frag_t *frag;
	int len = skb_headlen(skb);
	union enetc_tx_bd temp_bd;
	union enetc_tx_bd *txbd;
	bool do_vlan, do_tstamp;
	int i, count = 0;
	unsigned int f;
	dma_addr_t dma;
	u8 flags = 0;

	i = tx_ring->next_to_use;
	txbd = ENETC_TXBD(*tx_ring, i);
	prefetchw(txbd);

	dma = dma_map_single(tx_ring->dev, skb->data, len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(tx_ring->dev, dma)))
		goto dma_err;

	temp_bd.addr = cpu_to_le64(dma);
	temp_bd.buf_len = cpu_to_le16(len);
	temp_bd.lstatus = 0;

	tx_swbd = &tx_ring->tx_swbd[i];
	tx_swbd->dma = dma;
	tx_swbd->len = len;
	tx_swbd->is_dma_page = 0;
	count++;

	do_vlan = skb_vlan_tag_present(skb);
	do_tstamp = (active_offloads & ENETC_F_TX_TSTAMP) &&
		    (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP);
	tx_swbd->do_tstamp = do_tstamp;
	tx_swbd->check_wb = tx_swbd->do_tstamp;

	if (do_vlan || do_tstamp)
		flags |= ENETC_TXBD_FLAGS_EX;

	if (enetc_tx_csum(skb, &temp_bd))
		flags |= ENETC_TXBD_FLAGS_CSUM | ENETC_TXBD_FLAGS_L4CS;

	/* first BD needs frm_len and offload flags set */
	temp_bd.frm_len = cpu_to_le16(skb->len);
	temp_bd.flags = flags;

	if (flags & ENETC_TXBD_FLAGS_EX) {
		u8 e_flags = 0;
		*txbd = temp_bd;
		enetc_clear_tx_bd(&temp_bd);

		/* add extension BD for VLAN and/or timestamping */
		flags = 0;
		tx_swbd++;
		txbd++;
		i++;
		if (unlikely(i == tx_ring->bd_count)) {
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
			txbd = ENETC_TXBD(*tx_ring, 0);
		}
		prefetchw(txbd);

		if (do_vlan) {
			temp_bd.ext.vid = cpu_to_le16(skb_vlan_tag_get(skb));
			temp_bd.ext.tpid = 0; /* < C-TAG */
			e_flags |= ENETC_TXBD_E_FLAGS_VLAN_INS;
		}

		if (do_tstamp) {
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			e_flags |= ENETC_TXBD_E_FLAGS_TWO_STEP_PTP;
		}

		temp_bd.ext.e_flags = e_flags;
		count++;
	}

	frag = &skb_shinfo(skb)->frags[0];
	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++, frag++) {
		len = skb_frag_size(frag);
		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, len,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(tx_ring->dev, dma))
			goto dma_err;

		*txbd = temp_bd;
		enetc_clear_tx_bd(&temp_bd);

		flags = 0;
		tx_swbd++;
		txbd++;
		i++;
		if (unlikely(i == tx_ring->bd_count)) {
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
			txbd = ENETC_TXBD(*tx_ring, 0);
		}
		prefetchw(txbd);

		temp_bd.addr = cpu_to_le64(dma);
		temp_bd.buf_len = cpu_to_le16(len);

		tx_swbd->dma = dma;
		tx_swbd->len = len;
		tx_swbd->is_dma_page = 1;
		count++;
	}

	/* last BD needs 'F' bit set */
	flags |= ENETC_TXBD_FLAGS_F;
	temp_bd.flags = flags;
	*txbd = temp_bd;

	tx_ring->tx_swbd[i].skb = skb;

	enetc_bdr_idx_inc(tx_ring, &i);
	tx_ring->next_to_use = i;

	/* let H/W know BD ring has been updated */
	enetc_wr_reg(tx_ring->tpir, i); /* includes wmb() */

	return count;

dma_err:
	dev_err(tx_ring->dev, "DMA map error");

	do {
		tx_swbd = &tx_ring->tx_swbd[i];
		enetc_free_tx_skb(tx_ring, tx_swbd);
		if (i == 0)
			i = tx_ring->bd_count;
		i--;
	} while (count--);

	return 0;
}