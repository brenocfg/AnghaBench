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
struct sk_buff {int dummy; } ;
struct rx_tpa_end_cmp_ext {int dummy; } ;
struct rx_tpa_end_cmp {int dummy; } ;
struct bnxt_tpa_info {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sk_buff *bnxt_gro_skb(struct bnxt *bp,
					   struct bnxt_tpa_info *tpa_info,
					   struct rx_tpa_end_cmp *tpa_end,
					   struct rx_tpa_end_cmp_ext *tpa_end1,
					   struct sk_buff *skb)
{
#ifdef CONFIG_INET
	int payload_off;
	u16 segs;

	segs = TPA_END_TPA_SEGS(tpa_end);
	if (segs == 1)
		return skb;

	NAPI_GRO_CB(skb)->count = segs;
	skb_shinfo(skb)->gso_size =
		le32_to_cpu(tpa_end1->rx_tpa_end_cmp_seg_len);
	skb_shinfo(skb)->gso_type = tpa_info->gso_type;
	payload_off = (le32_to_cpu(tpa_end->rx_tpa_end_cmp_misc_v1) &
		       RX_TPA_END_CMP_PAYLOAD_OFFSET) >>
		      RX_TPA_END_CMP_PAYLOAD_OFFSET_SHIFT;
	skb = bp->gro_func(tpa_info, payload_off, TPA_END_GRO_TS(tpa_end), skb);
	if (likely(skb))
		tcp_gro_complete(skb);
#endif
	return skb;
}