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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct rx_tpa_end_cmp_ext {int /*<<< orphan*/  rx_tpa_end_cmp_seg_len; } ;
struct rx_tpa_end_cmp {int dummy; } ;
struct bnxt_tpa_info {int /*<<< orphan*/  gso_type; } ;
struct bnxt {int flags; struct sk_buff* (* gro_func ) (struct bnxt_tpa_info*,int,int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct TYPE_4__ {int count; } ;
struct TYPE_3__ {int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 TYPE_2__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TPA_END_GRO_TS (struct rx_tpa_end_cmp*) ; 
 int TPA_END_PAYLOAD_OFF (struct rx_tpa_end_cmp*) ; 
 int TPA_END_PAYLOAD_OFF_P5 (struct rx_tpa_end_cmp_ext*) ; 
 int TPA_END_TPA_SEGS (struct rx_tpa_end_cmp*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* stub1 (struct bnxt_tpa_info*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_gro_complete (struct sk_buff*) ; 

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
	if (bp->flags & BNXT_FLAG_CHIP_P5)
		payload_off = TPA_END_PAYLOAD_OFF_P5(tpa_end1);
	else
		payload_off = TPA_END_PAYLOAD_OFF(tpa_end);
	skb = bp->gro_func(tpa_info, payload_off, TPA_END_GRO_TS(tpa_end), skb);
	if (likely(skb))
		tcp_gro_complete(skb);
#endif
	return skb;
}