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
struct sk_buff {int /*<<< orphan*/  encapsulation; } ;
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T6 ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GSO_MASK ; 
 scalar_t__ cxgb_encap_offload_supported (struct sk_buff*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t cxgb_features_check(struct sk_buff *skb,
					     struct net_device *dev,
					     netdev_features_t features)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	if (CHELSIO_CHIP_VERSION(adapter->params.chip) < CHELSIO_T6)
		return features;

	/* Check if hw supports offload for this packet */
	if (!skb->encapsulation || cxgb_encap_offload_supported(skb))
		return features;

	/* Offload is not supported for this encapsulated packet */
	return features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}