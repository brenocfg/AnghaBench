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
struct net_device {int dummy; } ;
struct fec_enet_private {int pause_flag; } ;
struct ethtool_pauseparam {int autoneg; int tx_pause; int rx_pause; } ;

/* Variables and functions */
 int FEC_PAUSE_FLAG_AUTONEG ; 
 int FEC_PAUSE_FLAG_ENABLE ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fec_enet_get_pauseparam(struct net_device *ndev,
				    struct ethtool_pauseparam *pause)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	pause->autoneg = (fep->pause_flag & FEC_PAUSE_FLAG_AUTONEG) != 0;
	pause->tx_pause = (fep->pause_flag & FEC_PAUSE_FLAG_ENABLE) != 0;
	pause->rx_pause = pause->tx_pause;
}