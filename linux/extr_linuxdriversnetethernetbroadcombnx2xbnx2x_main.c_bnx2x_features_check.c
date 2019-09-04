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
struct TYPE_2__ {int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_GSO_MASK ; 
 int /*<<< orphan*/  skb_gso_validate_mac_len (struct sk_buff*,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_features_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_features_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_features_t bnx2x_features_check(struct sk_buff *skb,
					      struct net_device *dev,
					      netdev_features_t features)
{
	/*
	 * A skb with gso_size + header length > 9700 will cause a
	 * firmware panic. Drop GSO support.
	 *
	 * Eventually the upper layer should not pass these packets down.
	 *
	 * For speed, if the gso_size is <= 9000, assume there will
	 * not be 700 bytes of headers and pass it through. Only do a
	 * full (slow) validation if the gso_size is > 9000.
	 *
	 * (Due to the way SKB_BY_FRAGS works this will also do a full
	 * validation in that case.)
	 */
	if (unlikely(skb_is_gso(skb) &&
		     (skb_shinfo(skb)->gso_size > 9000) &&
		     !skb_gso_validate_mac_len(skb, 9700)))
		features &= ~NETIF_F_GSO_MASK;

	features = vlan_features_check(skb, features);
	return vxlan_features_check(skb, features);
}