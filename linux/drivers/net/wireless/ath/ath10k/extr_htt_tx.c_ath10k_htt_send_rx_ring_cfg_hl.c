#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct htt_rx_ring_setup_ring32 {void* flags; void* rx_ring_bufsize; void* rx_ring_len; } ;
struct TYPE_5__ {int num_rings; } ;
struct TYPE_6__ {TYPE_2__ hdr; struct htt_rx_ring_setup_ring32* rings; } ;
struct TYPE_4__ {int /*<<< orphan*/  msg_type; } ;
struct htt_cmd {TYPE_3__ rx_setup_32; TYPE_1__ hdr; } ;
struct ath10k_htt {int /*<<< orphan*/  eid; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  htc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HTT_H2T_MSG_TYPE_RX_RING_CFG ; 
 int HTT_MAX_CACHE_LINE_SIZE_MASK ; 
 int HTT_RX_BUF_SIZE ; 
 int HTT_RX_RING_FLAGS_MSDU_PAYLOAD ; 
 int HTT_RX_RING_FLAGS_MULTICAST_RX ; 
 int HTT_RX_RING_FLAGS_UNICAST_RX ; 
 int HTT_RX_RING_SIZE_MIN ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 void* __cpu_to_le16 (int) ; 
 struct sk_buff* ath10k_htc_alloc_skb (struct ath10k*,int) ; 
 int ath10k_htc_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct htt_rx_ring_setup_ring32*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int ath10k_htt_send_rx_ring_cfg_hl(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;
	struct sk_buff *skb;
	struct htt_cmd *cmd;
	struct htt_rx_ring_setup_ring32 *ring;
	const int num_rx_ring = 1;
	u16 flags;
	int len;
	int ret;

	/*
	 * the HW expects the buffer to be an integral number of 4-byte
	 * "words"
	 */
	BUILD_BUG_ON(!IS_ALIGNED(HTT_RX_BUF_SIZE, 4));
	BUILD_BUG_ON((HTT_RX_BUF_SIZE & HTT_MAX_CACHE_LINE_SIZE_MASK) != 0);

	len = sizeof(cmd->hdr) + sizeof(cmd->rx_setup_32.hdr)
	    + (sizeof(*ring) * num_rx_ring);
	skb = ath10k_htc_alloc_skb(ar, len);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, len);

	cmd = (struct htt_cmd *)skb->data;
	ring = &cmd->rx_setup_32.rings[0];

	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_RX_RING_CFG;
	cmd->rx_setup_32.hdr.num_rings = 1;

	flags = 0;
	flags |= HTT_RX_RING_FLAGS_MSDU_PAYLOAD;
	flags |= HTT_RX_RING_FLAGS_UNICAST_RX;
	flags |= HTT_RX_RING_FLAGS_MULTICAST_RX;

	memset(ring, 0, sizeof(*ring));
	ring->rx_ring_len = __cpu_to_le16(HTT_RX_RING_SIZE_MIN);
	ring->rx_ring_bufsize = __cpu_to_le16(HTT_RX_BUF_SIZE);
	ring->flags = __cpu_to_le16(flags);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	if (ret) {
		dev_kfree_skb_any(skb);
		return ret;
	}

	return 0;
}