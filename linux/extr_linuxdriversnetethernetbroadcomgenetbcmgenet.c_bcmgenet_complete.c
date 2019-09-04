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
struct bcmgenet_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bcmgenet_complete(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);

	/* Turn off the clock */
	clk_disable_unprepare(priv->clk);
}