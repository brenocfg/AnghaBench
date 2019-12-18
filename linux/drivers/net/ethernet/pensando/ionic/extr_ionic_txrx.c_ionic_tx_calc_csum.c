#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int encapsulation; scalar_t__ csum_not_inet; int /*<<< orphan*/  csum_offset; int /*<<< orphan*/  data; } ;
struct ionic_txq_desc {void* csum_offset; void* csum_start; void* vlan_tci; void* len; int /*<<< orphan*/  cmd; } ;
struct ionic_tx_stats {int /*<<< orphan*/  csum; int /*<<< orphan*/  crc32_csum; } ;
struct ionic_queue {TYPE_3__* lif; TYPE_1__* head; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  nr_frags; } ;
struct TYPE_7__ {TYPE_2__* ionic; } ;
struct TYPE_6__ {struct device* dev; } ;
struct TYPE_5__ {struct ionic_txq_desc* desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_ENCAP ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_FLAG_VLAN ; 
 int /*<<< orphan*/  IONIC_TXQ_DESC_OPCODE_CSUM_PARTIAL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_txq_desc_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_tx_map_single (struct ionic_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ionic_tx_stats* q_to_tx_stats (struct ionic_queue*) ; 
 int /*<<< orphan*/  skb_checksum_start_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int ionic_tx_calc_csum(struct ionic_queue *q, struct sk_buff *skb)
{
	struct ionic_tx_stats *stats = q_to_tx_stats(q);
	struct ionic_txq_desc *desc = q->head->desc;
	struct device *dev = q->lif->ionic->dev;
	dma_addr_t dma_addr;
	bool has_vlan;
	u8 flags = 0;
	bool encap;
	u64 cmd;

	has_vlan = !!skb_vlan_tag_present(skb);
	encap = skb->encapsulation;

	dma_addr = ionic_tx_map_single(q, skb->data, skb_headlen(skb));
	if (dma_mapping_error(dev, dma_addr))
		return -ENOMEM;

	flags |= has_vlan ? IONIC_TXQ_DESC_FLAG_VLAN : 0;
	flags |= encap ? IONIC_TXQ_DESC_FLAG_ENCAP : 0;

	cmd = encode_txq_desc_cmd(IONIC_TXQ_DESC_OPCODE_CSUM_PARTIAL,
				  flags, skb_shinfo(skb)->nr_frags, dma_addr);
	desc->cmd = cpu_to_le64(cmd);
	desc->len = cpu_to_le16(skb_headlen(skb));
	desc->vlan_tci = cpu_to_le16(skb_vlan_tag_get(skb));
	desc->csum_start = cpu_to_le16(skb_checksum_start_offset(skb));
	desc->csum_offset = cpu_to_le16(skb->csum_offset);

	if (skb->csum_not_inet)
		stats->crc32_csum++;
	else
		stats->csum++;

	return 0;
}