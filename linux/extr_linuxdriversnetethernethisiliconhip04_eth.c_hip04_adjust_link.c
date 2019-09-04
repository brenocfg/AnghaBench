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
struct phy_device {scalar_t__ speed; scalar_t__ duplex; } ;
struct net_device {int dummy; } ;
struct hip04_priv {scalar_t__ speed; scalar_t__ duplex; struct phy_device* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hip04_config_port (struct net_device*,scalar_t__,scalar_t__) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void hip04_adjust_link(struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	struct phy_device *phy = priv->phy;

	if ((priv->speed != phy->speed) || (priv->duplex != phy->duplex)) {
		hip04_config_port(ndev, phy->speed, phy->duplex);
		phy_print_status(phy);
	}
}