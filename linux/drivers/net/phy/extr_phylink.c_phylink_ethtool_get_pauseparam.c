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
struct TYPE_2__ {int pause; } ;
struct phylink {TYPE_1__ link_config; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int MLO_PAUSE_AN ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 

void phylink_ethtool_get_pauseparam(struct phylink *pl,
				    struct ethtool_pauseparam *pause)
{
	ASSERT_RTNL();

	pause->autoneg = !!(pl->link_config.pause & MLO_PAUSE_AN);
	pause->rx_pause = !!(pl->link_config.pause & MLO_PAUSE_RX);
	pause->tx_pause = !!(pl->link_config.pause & MLO_PAUSE_TX);
}