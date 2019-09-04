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
struct ks8695_priv {int in_suspend; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  ks8695_shutdown (struct ks8695_priv*) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int
ks8695_drv_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct ks8695_priv *ksp = netdev_priv(ndev);

	ksp->in_suspend = 1;

	if (netif_running(ndev)) {
		netif_device_detach(ndev);
		ks8695_shutdown(ksp);
	}

	return 0;
}