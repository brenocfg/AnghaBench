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
struct sky2_port {int /*<<< orphan*/  wol; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sky2_wol_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	const struct sky2_port *sky2 = netdev_priv(dev);

	wol->supported = sky2_wol_supported(sky2->hw);
	wol->wolopts = sky2->wol;
}