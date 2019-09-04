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
struct TYPE_2__ {int xmit_policy; } ;
struct bonding {TYPE_1__ params; } ;
typedef  enum netdev_lag_tx_type { ____Placeholder_netdev_lag_tx_type } netdev_lag_tx_type ;
typedef  enum netdev_lag_hash { ____Placeholder_netdev_lag_hash } netdev_lag_hash ;

/* Variables and functions */
#define  BOND_XMIT_POLICY_ENCAP23 132 
#define  BOND_XMIT_POLICY_ENCAP34 131 
#define  BOND_XMIT_POLICY_LAYER2 130 
#define  BOND_XMIT_POLICY_LAYER23 129 
#define  BOND_XMIT_POLICY_LAYER34 128 
 int NETDEV_LAG_HASH_E23 ; 
 int NETDEV_LAG_HASH_E34 ; 
 int NETDEV_LAG_HASH_L2 ; 
 int NETDEV_LAG_HASH_L23 ; 
 int NETDEV_LAG_HASH_L34 ; 
 int NETDEV_LAG_HASH_NONE ; 
 int NETDEV_LAG_HASH_UNKNOWN ; 
 int NETDEV_LAG_TX_TYPE_HASH ; 

__attribute__((used)) static enum netdev_lag_hash bond_lag_hash_type(struct bonding *bond,
					       enum netdev_lag_tx_type type)
{
	if (type != NETDEV_LAG_TX_TYPE_HASH)
		return NETDEV_LAG_HASH_NONE;

	switch (bond->params.xmit_policy) {
	case BOND_XMIT_POLICY_LAYER2:
		return NETDEV_LAG_HASH_L2;
	case BOND_XMIT_POLICY_LAYER34:
		return NETDEV_LAG_HASH_L34;
	case BOND_XMIT_POLICY_LAYER23:
		return NETDEV_LAG_HASH_L23;
	case BOND_XMIT_POLICY_ENCAP23:
		return NETDEV_LAG_HASH_E23;
	case BOND_XMIT_POLICY_ENCAP34:
		return NETDEV_LAG_HASH_E34;
	default:
		return NETDEV_LAG_HASH_UNKNOWN;
	}
}