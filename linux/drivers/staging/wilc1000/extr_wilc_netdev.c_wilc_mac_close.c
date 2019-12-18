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
struct wilc_vif {scalar_t__ mac_opened; scalar_t__ ndev; struct wilc* wilc; } ;
struct wilc {scalar_t__ open_ifcs; int close; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (scalar_t__) ; 
 int /*<<< orphan*/  wilc_deinit_host_int (scalar_t__) ; 
 int /*<<< orphan*/  wilc_wlan_deinitialize (struct net_device*) ; 

__attribute__((used)) static int wilc_mac_close(struct net_device *ndev)
{
	struct wilc_vif *vif = netdev_priv(ndev);
	struct wilc *wl = vif->wilc;

	netdev_dbg(ndev, "Mac close\n");

	if (wl->open_ifcs > 0)
		wl->open_ifcs--;
	else
		return 0;

	if (vif->ndev) {
		netif_stop_queue(vif->ndev);

		wilc_deinit_host_int(vif->ndev);
	}

	if (wl->open_ifcs == 0) {
		netdev_dbg(ndev, "Deinitializing wilc1000\n");
		wl->close = 1;
		wilc_wlan_deinitialize(ndev);
	}

	vif->mac_opened = 0;

	return 0;
}