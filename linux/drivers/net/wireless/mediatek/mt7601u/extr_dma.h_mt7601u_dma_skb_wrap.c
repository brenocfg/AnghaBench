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
struct sk_buff {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum mt76_msg_port { ____Placeholder_mt76_msg_port } mt76_msg_port ;
typedef  enum mt76_info_type { ____Placeholder_mt76_info_type } mt76_info_type ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_TXD_INFO_D_PORT ; 
 int /*<<< orphan*/  MT_TXD_INFO_LEN ; 
 int /*<<< orphan*/  MT_TXD_INFO_TYPE ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ ) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int skb_put_padto (struct sk_buff*,int) ; 

__attribute__((used)) static inline int mt7601u_dma_skb_wrap(struct sk_buff *skb,
				       enum mt76_msg_port d_port,
				       enum mt76_info_type type, u32 flags)
{
	u32 info;

	/* Buffer layout:
	 *	|   4B   | xfer len |      pad       |  4B  |
	 *	| TXINFO | pkt/cmd  | zero pad to 4B | zero |
	 *
	 * length field of TXINFO should be set to 'xfer len'.
	 */

	info = flags |
		FIELD_PREP(MT_TXD_INFO_LEN, round_up(skb->len, 4)) |
		FIELD_PREP(MT_TXD_INFO_D_PORT, d_port) |
		FIELD_PREP(MT_TXD_INFO_TYPE, type);

	put_unaligned_le32(info, skb_push(skb, sizeof(info)));
	return skb_put_padto(skb, round_up(skb->len, 4) + 4);
}