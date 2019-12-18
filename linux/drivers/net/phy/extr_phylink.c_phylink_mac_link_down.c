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
struct phylink {int /*<<< orphan*/  cur_interface; int /*<<< orphan*/  link_an_mode; int /*<<< orphan*/  config; TYPE_1__* ops; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mac_link_down ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phylink_info (struct phylink*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_mac_link_down(struct phylink *pl)
{
	struct net_device *ndev = pl->netdev;

	if (ndev)
		netif_carrier_off(ndev);
	pl->ops->mac_link_down(pl->config, pl->link_an_mode,
			       pl->cur_interface);
	phylink_info(pl, "Link is Down\n");
}