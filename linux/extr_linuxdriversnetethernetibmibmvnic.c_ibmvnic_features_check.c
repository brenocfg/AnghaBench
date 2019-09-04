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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {int gso_size; int gso_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_GSO_MASK ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static netdev_features_t ibmvnic_features_check(struct sk_buff *skb,
						struct net_device *dev,
						netdev_features_t features)
{
	/* Some backing hardware adapters can not
	 * handle packets with a MSS less than 224
	 * or with only one segment.
	 */
	if (skb_is_gso(skb)) {
		if (skb_shinfo(skb)->gso_size < 224 ||
		    skb_shinfo(skb)->gso_segs == 1)
			features &= ~NETIF_F_GSO_MASK;
	}

	return features;
}