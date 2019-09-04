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
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcmgenet_begin(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);

	/* Turn on the clock */
	return clk_prepare_enable(priv->clk);
}