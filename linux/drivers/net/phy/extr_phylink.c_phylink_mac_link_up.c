#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phylink_link_state {int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  interface; } ;
struct TYPE_4__ {int /*<<< orphan*/  interface; } ;
struct phylink {int /*<<< orphan*/  phydev; TYPE_2__ phy_state; int /*<<< orphan*/  link_an_mode; int /*<<< orphan*/  config; TYPE_1__* ops; int /*<<< orphan*/  cur_interface; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mac_link_up ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  phy_duplex_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_speed_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_info (struct phylink*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_pause_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_mac_link_up(struct phylink *pl,
				struct phylink_link_state link_state)
{
	struct net_device *ndev = pl->netdev;

	pl->cur_interface = link_state.interface;
	pl->ops->mac_link_up(pl->config, pl->link_an_mode,
			     pl->phy_state.interface,
			     pl->phydev);

	if (ndev)
		netif_carrier_on(ndev);

	phylink_info(pl,
		     "Link is Up - %s/%s - flow control %s\n",
		     phy_speed_to_str(link_state.speed),
		     phy_duplex_to_str(link_state.duplex),
		     phylink_pause_to_str(link_state.pause));
}