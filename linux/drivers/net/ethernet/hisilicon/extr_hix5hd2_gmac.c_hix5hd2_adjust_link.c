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
struct net_device {struct phy_device* phydev; } ;
struct hix5hd2_priv {scalar_t__ speed; scalar_t__ duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  hix5hd2_config_port (struct net_device*,scalar_t__,scalar_t__) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void hix5hd2_adjust_link(struct net_device *dev)
{
	struct hix5hd2_priv *priv = netdev_priv(dev);
	struct phy_device *phy = dev->phydev;

	if ((priv->speed != phy->speed) || (priv->duplex != phy->duplex)) {
		hix5hd2_config_port(dev, phy->speed, phy->duplex);
		phy_print_status(phy);
	}
}