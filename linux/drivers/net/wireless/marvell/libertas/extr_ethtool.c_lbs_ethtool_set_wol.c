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
struct lbs_private {int /*<<< orphan*/  wol_criteria; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHS_REMOVE_WAKEUP ; 
 int /*<<< orphan*/  EHS_WAKE_ON_BROADCAST_DATA ; 
 int /*<<< orphan*/  EHS_WAKE_ON_MAC_EVENT ; 
 int /*<<< orphan*/  EHS_WAKE_ON_MULTICAST_DATA ; 
 int /*<<< orphan*/  EHS_WAKE_ON_UNICAST_DATA ; 
 int EOPNOTSUPP ; 
 int WAKE_BCAST ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 

__attribute__((used)) static int lbs_ethtool_set_wol(struct net_device *dev,
			       struct ethtool_wolinfo *wol)
{
	struct lbs_private *priv = dev->ml_priv;

	if (wol->wolopts & ~(WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY))
		return -EOPNOTSUPP;

	priv->wol_criteria = 0;
	if (wol->wolopts & WAKE_UCAST)
		priv->wol_criteria |= EHS_WAKE_ON_UNICAST_DATA;
	if (wol->wolopts & WAKE_MCAST)
		priv->wol_criteria |= EHS_WAKE_ON_MULTICAST_DATA;
	if (wol->wolopts & WAKE_BCAST)
		priv->wol_criteria |= EHS_WAKE_ON_BROADCAST_DATA;
	if (wol->wolopts & WAKE_PHY)
		priv->wol_criteria |= EHS_WAKE_ON_MAC_EVENT;
	if (wol->wolopts == 0)
		priv->wol_criteria |= EHS_REMOVE_WAKEUP;
	return 0;
}