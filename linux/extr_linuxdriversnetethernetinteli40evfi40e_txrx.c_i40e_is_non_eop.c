#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union i40e_rx_desc {int dummy; } i40e_rx_desc ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  non_eop_descs; } ;
struct i40e_ring {int next_to_clean; int count; TYPE_1__ rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_RX_DESC (struct i40e_ring*,int) ; 
 int /*<<< orphan*/  I40E_RX_DESC_STATUS_EOF_SHIFT ; 
 int /*<<< orphan*/  i40e_test_staterr (union i40e_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40e_is_non_eop(struct i40e_ring *rx_ring,
			    union i40e_rx_desc *rx_desc,
			    struct sk_buff *skb)
{
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(I40E_RX_DESC(rx_ring, ntc));

	/* if we are the last buffer then there is nothing else to do */
#define I40E_RXD_EOF BIT(I40E_RX_DESC_STATUS_EOF_SHIFT)
	if (likely(i40e_test_staterr(rx_desc, I40E_RXD_EOF)))
		return false;

	rx_ring->rx_stats.non_eop_descs++;

	return true;
}