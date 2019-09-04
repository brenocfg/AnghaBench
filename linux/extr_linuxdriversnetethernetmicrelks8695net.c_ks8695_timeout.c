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
struct ks8695_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks8695_init_net (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_reset (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  ks8695_shutdown (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_update_mac (struct ks8695_priv*) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static void
ks8695_timeout(struct net_device *ndev)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);

	netif_stop_queue(ndev);
	ks8695_shutdown(ksp);

	ks8695_reset(ksp);

	ks8695_update_mac(ksp);

	/* We ignore the return from this since it managed to init
	 * before it probably will be okay to init again.
	 */
	ks8695_init_net(ksp);

	/* Reconfigure promiscuity etc */
	ks8695_set_multicast(ndev);

	/* And start the TX queue once more */
	netif_start_queue(ndev);
}