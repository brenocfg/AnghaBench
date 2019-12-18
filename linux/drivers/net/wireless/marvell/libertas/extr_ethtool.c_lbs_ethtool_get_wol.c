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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int wol_criteria; } ;
struct ethtool_wolinfo {int supported; int wolopts; } ;

/* Variables and functions */
 int EHS_REMOVE_WAKEUP ; 
 int EHS_WAKE_ON_BROADCAST_DATA ; 
 int EHS_WAKE_ON_MAC_EVENT ; 
 int EHS_WAKE_ON_MULTICAST_DATA ; 
 int EHS_WAKE_ON_UNICAST_DATA ; 
 int WAKE_BCAST ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 

__attribute__((used)) static void lbs_ethtool_get_wol(struct net_device *dev,
				struct ethtool_wolinfo *wol)
{
	struct lbs_private *priv = dev->ml_priv;

	wol->supported = WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY;

	if (priv->wol_criteria == EHS_REMOVE_WAKEUP)
		return;

	if (priv->wol_criteria & EHS_WAKE_ON_UNICAST_DATA)
		wol->wolopts |= WAKE_UCAST;
	if (priv->wol_criteria & EHS_WAKE_ON_MULTICAST_DATA)
		wol->wolopts |= WAKE_MCAST;
	if (priv->wol_criteria & EHS_WAKE_ON_BROADCAST_DATA)
		wol->wolopts |= WAKE_BCAST;
	if (priv->wol_criteria & EHS_WAKE_ON_MAC_EVENT)
		wol->wolopts |= WAKE_PHY;
}