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
struct sk_buff {int /*<<< orphan*/  encapsulation; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GSO_MASK ; 
 scalar_t__ fm10k_tx_encap_offload (struct sk_buff*) ; 

__attribute__((used)) static netdev_features_t fm10k_features_check(struct sk_buff *skb,
					      struct net_device *dev,
					      netdev_features_t features)
{
	if (!skb->encapsulation || fm10k_tx_encap_offload(skb))
		return features;

	return features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}