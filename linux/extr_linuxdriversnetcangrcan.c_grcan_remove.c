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
struct net_device {int /*<<< orphan*/  irq; } ;
struct grcan_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 

__attribute__((used)) static int grcan_remove(struct platform_device *ofdev)
{
	struct net_device *dev = platform_get_drvdata(ofdev);
	struct grcan_priv *priv = netdev_priv(dev);

	unregister_candev(dev); /* Will in turn call grcan_close */

	irq_dispose_mapping(dev->irq);
	netif_napi_del(&priv->napi);
	free_candev(dev);

	return 0;
}