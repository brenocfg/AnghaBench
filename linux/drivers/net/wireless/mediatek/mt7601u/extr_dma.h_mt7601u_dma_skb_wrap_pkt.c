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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
typedef  enum mt76_qsel { ____Placeholder_mt76_qsel } mt76_qsel ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PACKET ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_TXD_PKT_INFO_QSEL ; 
 int /*<<< orphan*/  WLAN_PORT ; 
 int mt7601u_dma_skb_wrap (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mt7601u_dma_skb_wrap_pkt(struct sk_buff *skb, enum mt76_qsel qsel, u32 flags)
{
	flags |= FIELD_PREP(MT_TXD_PKT_INFO_QSEL, qsel);
	return mt7601u_dma_skb_wrap(skb, WLAN_PORT, DMA_PACKET, flags);
}