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
struct bnx2x {int /*<<< orphan*/  accept_any_vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ACCEPT_ALL_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_ALL_UNICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_ANY_VLAN ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_BROADCAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_UNICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_UNMATCHED ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_RX_MODE_ALLMULTI 131 
#define  BNX2X_RX_MODE_NONE 130 
#define  BNX2X_RX_MODE_NORMAL 129 
#define  BNX2X_RX_MODE_PROMISC 128 
 int EINVAL ; 
 int /*<<< orphan*/  IS_MF_SI (struct bnx2x*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int bnx2x_fill_accept_flags(struct bnx2x *bp, u32 rx_mode,
				   unsigned long *rx_accept_flags,
				   unsigned long *tx_accept_flags)
{
	/* Clear the flags first */
	*rx_accept_flags = 0;
	*tx_accept_flags = 0;

	switch (rx_mode) {
	case BNX2X_RX_MODE_NONE:
		/*
		 * 'drop all' supersedes any accept flags that may have been
		 * passed to the function.
		 */
		break;
	case BNX2X_RX_MODE_NORMAL:
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* internal switching mode */
		__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		if (bp->accept_any_vlan) {
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);
		}

		break;
	case BNX2X_RX_MODE_ALLMULTI:
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* internal switching mode */
		__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		if (bp->accept_any_vlan) {
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);
		}

		break;
	case BNX2X_RX_MODE_PROMISC:
		/* According to definition of SI mode, iface in promisc mode
		 * should receive matched and unmatched (in resolution of port)
		 * unicast packets.
		 */
		__set_bit(BNX2X_ACCEPT_UNMATCHED, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* internal switching mode */
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		if (IS_MF_SI(bp))
			__set_bit(BNX2X_ACCEPT_ALL_UNICAST, tx_accept_flags);
		else
			__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);

		__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);

		break;
	default:
		BNX2X_ERR("Unknown rx_mode: %d\n", rx_mode);
		return -EINVAL;
	}

	return 0;
}