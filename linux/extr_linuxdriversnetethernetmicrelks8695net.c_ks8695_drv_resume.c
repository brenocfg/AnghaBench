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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ks8695_priv {scalar_t__ in_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks8695_init_net (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_reset (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_set_multicast (struct net_device*) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int
ks8695_drv_resume(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct ks8695_priv *ksp = netdev_priv(ndev);

	if (netif_running(ndev)) {
		ks8695_reset(ksp);
		ks8695_init_net(ksp);
		ks8695_set_multicast(ndev);
		netif_device_attach(ndev);
	}

	ksp->in_suspend = 0;

	return 0;
}