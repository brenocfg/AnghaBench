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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int u32 ;
struct ixgbevf_ring {int next_to_clean; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBEVF_RX_DESC (struct ixgbevf_ring*,int) ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_EOP ; 
 int /*<<< orphan*/  ixgbevf_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ixgbevf_is_non_eop(struct ixgbevf_ring *rx_ring,
			       union ixgbe_adv_rx_desc *rx_desc)
{
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IXGBEVF_RX_DESC(rx_ring, ntc));

	if (likely(ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)))
		return false;

	return true;
}