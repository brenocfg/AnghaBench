#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rockchip_priv_data {int /*<<< orphan*/  macclk; TYPE_1__* soc_data; scalar_t__ regulator; int /*<<< orphan*/  refclk; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ need_div_macclk; } ;

/* Variables and functions */
 int arc_emac_remove (struct net_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct rockchip_priv_data* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static int emac_rockchip_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct rockchip_priv_data *priv = netdev_priv(ndev);
	int err;

	err = arc_emac_remove(ndev);

	clk_disable_unprepare(priv->refclk);

	if (priv->regulator)
		regulator_disable(priv->regulator);

	if (priv->soc_data->need_div_macclk)
		clk_disable_unprepare(priv->macclk);

	free_netdev(ndev);
	return err;
}