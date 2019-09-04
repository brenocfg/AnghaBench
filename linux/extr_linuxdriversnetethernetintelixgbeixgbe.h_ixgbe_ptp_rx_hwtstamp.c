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
struct sk_buff {int dummy; } ;
struct ixgbe_ring {int /*<<< orphan*/  last_rx_timestamp; int /*<<< orphan*/  q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_RXDADV_STAT_TS ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_TSIP ; 
 int /*<<< orphan*/  ixgbe_ptp_rx_pktstamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_ptp_rx_rgtstamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void ixgbe_ptp_rx_hwtstamp(struct ixgbe_ring *rx_ring,
					 union ixgbe_adv_rx_desc *rx_desc,
					 struct sk_buff *skb)
{
	if (unlikely(ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_TSIP))) {
		ixgbe_ptp_rx_pktstamp(rx_ring->q_vector, skb);
		return;
	}

	if (unlikely(!ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_STAT_TS)))
		return;

	ixgbe_ptp_rx_rgtstamp(rx_ring->q_vector, skb);

	/* Update the last_rx_timestamp timer in order to enable watchdog check
	 * for error case of latched timestamp on a dropped packet.
	 */
	rx_ring->last_rx_timestamp = jiffies;
}