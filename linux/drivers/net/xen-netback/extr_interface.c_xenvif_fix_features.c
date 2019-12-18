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
struct xenvif {int gso_mask; int /*<<< orphan*/  ipv6_csum; int /*<<< orphan*/  ip_csum; int /*<<< orphan*/  can_sg; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int GSO_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  NETIF_F_TSO6 ; 
 int /*<<< orphan*/  TCPV4 ; 
 int /*<<< orphan*/  TCPV6 ; 
 struct xenvif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t xenvif_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct xenvif *vif = netdev_priv(dev);

	if (!vif->can_sg)
		features &= ~NETIF_F_SG;
	if (~(vif->gso_mask) & GSO_BIT(TCPV4))
		features &= ~NETIF_F_TSO;
	if (~(vif->gso_mask) & GSO_BIT(TCPV6))
		features &= ~NETIF_F_TSO6;
	if (!vif->ip_csum)
		features &= ~NETIF_F_IP_CSUM;
	if (!vif->ipv6_csum)
		features &= ~NETIF_F_IPV6_CSUM;

	return features;
}