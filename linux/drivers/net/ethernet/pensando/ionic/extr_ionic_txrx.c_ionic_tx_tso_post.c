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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ionic_txq_desc {void* mss; void* hdr_len; void* vlan_tci; void* len; int /*<<< orphan*/  cmd; } ;
struct ionic_queue {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_ENCAP ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_TSO_EOT ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_TSO_SOT ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_VLAN ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_OPCODE_TSO ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_txq_desc_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_tx_clean ; 
 int /*<<< orphan*/  ionic_txq_post (struct ionic_queue*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  q_to_ndq (struct ionic_queue*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 

__attribute__((used)) static void ionic_tx_tso_post(struct ionic_queue *q, struct ionic_txq_desc *desc,
			      struct sk_buff *skb,
			      dma_addr_t addr, u8 nsge, u16 len,
			      unsigned int hdrlen, unsigned int mss,
			      bool outer_csum,
			      u16 vlan_tci, bool has_vlan,
			      bool start, bool done)
{
	u8 flags = 0;
	u64 cmd;

	flags |= has_vlan ? IONIC_TXQ_DESC_FLAG_VLAN : 0;
	flags |= outer_csum ? IONIC_TXQ_DESC_FLAG_ENCAP : 0;
	flags |= start ? IONIC_TXQ_DESC_FLAG_TSO_SOT : 0;
	flags |= done ? IONIC_TXQ_DESC_FLAG_TSO_EOT : 0;

	cmd = encode_txq_desc_cmd(IONIC_TXQ_DESC_OPCODE_TSO, flags, nsge, addr);
	desc->cmd = cpu_to_le64(cmd);
	desc->len = cpu_to_le16(len);
	desc->vlan_tci = cpu_to_le16(vlan_tci);
	desc->hdr_len = cpu_to_le16(hdrlen);
	desc->mss = cpu_to_le16(mss);

	if (done) {
		skb_tx_timestamp(skb);
		netdev_tx_sent_queue(q_to_ndq(q), skb->len);
		ionic_txq_post(q, !netdev_xmit_more(), ionic_tx_clean, skb);
	} else {
		ionic_txq_post(q, false, ionic_tx_clean, NULL);
	}
}