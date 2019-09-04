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
struct flexcan_priv {int /*<<< orphan*/  offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_rx_offload_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 struct flexcan_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_flexcandev (struct net_device*) ; 

__attribute__((used)) static int flexcan_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct flexcan_priv *priv = netdev_priv(dev);

	unregister_flexcandev(dev);
	can_rx_offload_del(&priv->offload);
	free_candev(dev);

	return 0;
}