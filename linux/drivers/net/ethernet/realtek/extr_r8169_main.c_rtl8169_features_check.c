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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; } ;
struct rtl8169_private {int mac_version; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ ETH_ZLEN ; 
 int GTTCPHO_MAX ; 
 int /*<<< orphan*/  NETIF_F_ALL_TSO ; 
 int /*<<< orphan*/  NETIF_F_CSUM_MASK ; 
#define  RTL_GIGA_MAC_VER_11 131 
#define  RTL_GIGA_MAC_VER_12 130 
#define  RTL_GIGA_MAC_VER_17 129 
#define  RTL_GIGA_MAC_VER_34 128 
 int TCPHO_MAX ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 scalar_t__ rtl_chip_supports_csum_v2 (struct rtl8169_private*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_features_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_features_t rtl8169_features_check(struct sk_buff *skb,
						struct net_device *dev,
						netdev_features_t features)
{
	int transport_offset = skb_transport_offset(skb);
	struct rtl8169_private *tp = netdev_priv(dev);

	if (skb_is_gso(skb)) {
		if (transport_offset > GTTCPHO_MAX &&
		    rtl_chip_supports_csum_v2(tp))
			features &= ~NETIF_F_ALL_TSO;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (skb->len < ETH_ZLEN) {
			switch (tp->mac_version) {
			case RTL_GIGA_MAC_VER_11:
			case RTL_GIGA_MAC_VER_12:
			case RTL_GIGA_MAC_VER_17:
			case RTL_GIGA_MAC_VER_34:
				features &= ~NETIF_F_CSUM_MASK;
				break;
			default:
				break;
			}
		}

		if (transport_offset > TCPHO_MAX &&
		    rtl_chip_supports_csum_v2(tp))
			features &= ~NETIF_F_CSUM_MASK;
	}

	return vlan_features_check(skb, features);
}