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
struct nps_enet_priv {int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_hw_disable_control (struct net_device*) ; 

__attribute__((used)) static s32 nps_enet_stop(struct net_device *ndev)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);
	netif_stop_queue(ndev);
	nps_enet_hw_disable_control(ndev);
	free_irq(priv->irq, ndev);

	return 0;
}