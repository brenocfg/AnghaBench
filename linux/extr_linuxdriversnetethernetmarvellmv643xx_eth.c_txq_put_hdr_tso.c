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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tx_queue {int tx_curr_desc; int tx_ring_size; scalar_t__ tso_hdrs_dma; struct tx_desc* tx_desc_area; } ;
struct tx_desc {int byte_cnt; int cmd_sts; scalar_t__ buf_ptr; scalar_t__ l4i_chk; } ;
struct sk_buff {int dummy; } ;
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int BUFFER_OWNED_BY_DMA ; 
 int GEN_CRC ; 
 int TSO_HEADER_SIZE ; 
 int TX_FIRST_DESC ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int skb_tx_csum (struct mv643xx_eth_private*,struct sk_buff*,int /*<<< orphan*/ *,int*,int) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 

__attribute__((used)) static inline void
txq_put_hdr_tso(struct sk_buff *skb, struct tx_queue *txq, int length,
		u32 *first_cmd_sts, bool first_desc)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);
	int hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	int tx_index;
	struct tx_desc *desc;
	int ret;
	u32 cmd_csum = 0;
	u16 l4i_chk = 0;
	u32 cmd_sts;

	tx_index = txq->tx_curr_desc;
	desc = &txq->tx_desc_area[tx_index];

	ret = skb_tx_csum(mp, skb, &l4i_chk, &cmd_csum, length);
	if (ret)
		WARN(1, "failed to prepare checksum!");

	/* Should we set this? Can't use the value from skb_tx_csum()
	 * as it's not the correct initial L4 checksum to use. */
	desc->l4i_chk = 0;

	desc->byte_cnt = hdr_len;
	desc->buf_ptr = txq->tso_hdrs_dma +
			txq->tx_curr_desc * TSO_HEADER_SIZE;
	cmd_sts = cmd_csum | BUFFER_OWNED_BY_DMA  | TX_FIRST_DESC |
				   GEN_CRC;

	/* Defer updating the first command descriptor until all
	 * following descriptors have been written.
	 */
	if (first_desc)
		*first_cmd_sts = cmd_sts;
	else
		desc->cmd_sts = cmd_sts;

	txq->tx_curr_desc++;
	if (txq->tx_curr_desc == txq->tx_ring_size)
		txq->tx_curr_desc = 0;
}