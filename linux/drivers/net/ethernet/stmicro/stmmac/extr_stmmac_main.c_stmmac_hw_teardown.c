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
struct stmmac_priv {TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk_ptp_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void stmmac_hw_teardown(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	clk_disable_unprepare(priv->plat->clk_ptp_ref);
}