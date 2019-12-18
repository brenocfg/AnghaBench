#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  rss; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkt_info; } ;
struct TYPE_9__ {TYPE_2__ hs_rss; } ;
struct TYPE_11__ {TYPE_4__ hi_dword; TYPE_3__ lo_dword; } ;
struct TYPE_12__ {TYPE_5__ lower; } ;
union ixgbe_adv_rx_desc {TYPE_6__ wb; } ;
typedef  unsigned long u16 ;
struct sk_buff {int dummy; } ;
struct ixgbevf_ring {TYPE_1__* netdev; } ;
struct TYPE_7__ {int features; } ;

/* Variables and functions */
 unsigned long IXGBE_RSS_L4_TYPES_MASK ; 
 unsigned long IXGBE_RXDADV_RSSTYPE_MASK ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ixgbevf_rx_hash(struct ixgbevf_ring *ring,
				   union ixgbe_adv_rx_desc *rx_desc,
				   struct sk_buff *skb)
{
	u16 rss_type;

	if (!(ring->netdev->features & NETIF_F_RXHASH))
		return;

	rss_type = le16_to_cpu(rx_desc->wb.lower.lo_dword.hs_rss.pkt_info) &
		   IXGBE_RXDADV_RSSTYPE_MASK;

	if (!rss_type)
		return;

	skb_set_hash(skb, le32_to_cpu(rx_desc->wb.lower.hi_dword.rss),
		     (IXGBE_RSS_L4_TYPES_MASK & (1ul << rss_type)) ?
		     PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3);
}