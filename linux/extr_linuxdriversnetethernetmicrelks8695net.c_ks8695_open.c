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
struct ks8695_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int ks8695_init_net (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_reset (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_shutdown (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_update_mac (struct ks8695_priv*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static int
ks8695_open(struct net_device *ndev)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	int ret;

	ks8695_reset(ksp);

	ks8695_update_mac(ksp);

	ret = ks8695_init_net(ksp);
	if (ret) {
		ks8695_shutdown(ksp);
		return ret;
	}

	napi_enable(&ksp->napi);
	netif_start_queue(ndev);

	return 0;
}