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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bonding {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int BOND_MODE (struct bonding*) ; 
#define  BOND_MODE_8023AD 134 
#define  BOND_MODE_ACTIVEBACKUP 133 
#define  BOND_MODE_ALB 132 
#define  BOND_MODE_BROADCAST 131 
#define  BOND_MODE_ROUNDROBIN 130 
#define  BOND_MODE_TLB 129 
#define  BOND_MODE_XOR 128 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bond_3ad_xor_xmit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  bond_alb_xmit (struct sk_buff*,struct net_device*) ; 
 scalar_t__ bond_should_override_tx_queue (struct bonding*) ; 
 int /*<<< orphan*/  bond_slave_override (struct bonding*,struct sk_buff*) ; 
 int /*<<< orphan*/  bond_tlb_xmit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  bond_tx_drop (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  bond_xmit_activebackup (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  bond_xmit_broadcast (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  bond_xmit_roundrobin (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t __bond_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bonding *bond = netdev_priv(dev);

	if (bond_should_override_tx_queue(bond) &&
	    !bond_slave_override(bond, skb))
		return NETDEV_TX_OK;

	switch (BOND_MODE(bond)) {
	case BOND_MODE_ROUNDROBIN:
		return bond_xmit_roundrobin(skb, dev);
	case BOND_MODE_ACTIVEBACKUP:
		return bond_xmit_activebackup(skb, dev);
	case BOND_MODE_8023AD:
	case BOND_MODE_XOR:
		return bond_3ad_xor_xmit(skb, dev);
	case BOND_MODE_BROADCAST:
		return bond_xmit_broadcast(skb, dev);
	case BOND_MODE_ALB:
		return bond_alb_xmit(skb, dev);
	case BOND_MODE_TLB:
		return bond_tlb_xmit(skb, dev);
	default:
		/* Should never happen, mode already checked */
		netdev_err(dev, "Unknown bonding mode %d\n", BOND_MODE(bond));
		WARN_ON_ONCE(1);
		bond_tx_drop(dev, skb);
		return NETDEV_TX_OK;
	}
}