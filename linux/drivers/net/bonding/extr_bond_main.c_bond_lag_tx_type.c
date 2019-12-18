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
struct bonding {int dummy; } ;
typedef  enum netdev_lag_tx_type { ____Placeholder_netdev_lag_tx_type } netdev_lag_tx_type ;

/* Variables and functions */
 int BOND_MODE (struct bonding*) ; 
#define  BOND_MODE_8023AD 132 
#define  BOND_MODE_ACTIVEBACKUP 131 
#define  BOND_MODE_BROADCAST 130 
#define  BOND_MODE_ROUNDROBIN 129 
#define  BOND_MODE_XOR 128 
 int NETDEV_LAG_TX_TYPE_ACTIVEBACKUP ; 
 int NETDEV_LAG_TX_TYPE_BROADCAST ; 
 int NETDEV_LAG_TX_TYPE_HASH ; 
 int NETDEV_LAG_TX_TYPE_ROUNDROBIN ; 
 int NETDEV_LAG_TX_TYPE_UNKNOWN ; 

__attribute__((used)) static enum netdev_lag_tx_type bond_lag_tx_type(struct bonding *bond)
{
	switch (BOND_MODE(bond)) {
	case BOND_MODE_ROUNDROBIN:
		return NETDEV_LAG_TX_TYPE_ROUNDROBIN;
	case BOND_MODE_ACTIVEBACKUP:
		return NETDEV_LAG_TX_TYPE_ACTIVEBACKUP;
	case BOND_MODE_BROADCAST:
		return NETDEV_LAG_TX_TYPE_BROADCAST;
	case BOND_MODE_XOR:
	case BOND_MODE_8023AD:
		return NETDEV_LAG_TX_TYPE_HASH;
	default:
		return NETDEV_LAG_TX_TYPE_UNKNOWN;
	}
}