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
struct skge_port {int /*<<< orphan*/  wol; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wol_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct skge_port *skge = netdev_priv(dev);

	wol->supported = wol_supported(skge->hw);
	wol->wolopts = skge->wol;
}