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
struct net_device {int mtu; } ;
struct gem {scalar_t__ lstate; int /*<<< orphan*/  cell_enabled; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gem_netif_start (struct gem*) ; 
 int /*<<< orphan*/  gem_netif_stop (struct gem*) ; 
 int /*<<< orphan*/  gem_reinit_chip (struct gem*) ; 
 int /*<<< orphan*/  gem_set_link_modes (struct gem*) ; 
 scalar_t__ link_up ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int gem_change_mtu(struct net_device *dev, int new_mtu)
{
	struct gem *gp = netdev_priv(dev);

	dev->mtu = new_mtu;

	/* We'll just catch it later when the device is up'd or resumed */
	if (!netif_running(dev) || !netif_device_present(dev))
		return 0;

	/* Better safe than sorry... */
	if (WARN_ON(!gp->cell_enabled))
		return 0;

	gem_netif_stop(gp);
	gem_reinit_chip(gp);
	if (gp->lstate == link_up)
		gem_set_link_modes(gp);
	gem_netif_start(gp);

	return 0;
}