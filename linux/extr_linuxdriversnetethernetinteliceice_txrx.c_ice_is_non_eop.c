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
typedef  union ice_32b_rx_flex_desc {int dummy; } ice_32b_rx_flex_desc ;
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  non_eop_descs; } ;
struct ice_ring {int next_to_clean; size_t count; TYPE_1__ rx_stats; TYPE_2__* rx_buf; } ;
struct TYPE_4__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICE_RX_DESC (struct ice_ring*,size_t) ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_EOF_S ; 
 int /*<<< orphan*/  ice_test_staterr (union ice_32b_rx_flex_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_is_non_eop(struct ice_ring *rx_ring,
			   union ice_32b_rx_flex_desc *rx_desc,
			   struct sk_buff *skb)
{
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(ICE_RX_DESC(rx_ring, ntc));

	/* if we are the last buffer then there is nothing else to do */
#define ICE_RXD_EOF BIT(ICE_RX_FLEX_DESC_STATUS0_EOF_S)
	if (likely(ice_test_staterr(rx_desc, ICE_RXD_EOF)))
		return false;

	/* place skb in next buffer to be received */
	rx_ring->rx_buf[ntc].skb = skb;
	rx_ring->rx_stats.non_eop_descs++;

	return true;
}