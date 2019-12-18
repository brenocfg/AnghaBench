#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;
struct xrx200_priv {int /*<<< orphan*/  clk; TYPE_2__ chan_rx; TYPE_1__ chan_tx; struct net_device* net_dev; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 struct xrx200_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  xrx200_hw_cleanup (struct xrx200_priv*) ; 

__attribute__((used)) static int xrx200_remove(struct platform_device *pdev)
{
	struct xrx200_priv *priv = platform_get_drvdata(pdev);
	struct net_device *net_dev = priv->net_dev;

	/* free stack related instances */
	netif_stop_queue(net_dev);
	netif_napi_del(&priv->chan_tx.napi);
	netif_napi_del(&priv->chan_rx.napi);

	/* remove the actual device */
	unregister_netdev(net_dev);

	/* release the clock */
	clk_disable_unprepare(priv->clk);

	/* shut down hardware */
	xrx200_hw_cleanup(priv);

	return 0;
}