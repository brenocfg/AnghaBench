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
struct rcar_can_priv {int /*<<< orphan*/  clk; TYPE_1__* regs; } ;
struct net_device {int dummy; } ;
struct can_berr_counter {void* rxerr; void* txerr; } ;
struct TYPE_2__ {int /*<<< orphan*/  recr; int /*<<< orphan*/  tecr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct rcar_can_priv* netdev_priv (struct net_device const*) ; 
 void* readb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_can_get_berr_counter(const struct net_device *dev,
				     struct can_berr_counter *bec)
{
	struct rcar_can_priv *priv = netdev_priv(dev);
	int err;

	err = clk_prepare_enable(priv->clk);
	if (err)
		return err;
	bec->txerr = readb(&priv->regs->tecr);
	bec->rxerr = readb(&priv->regs->recr);
	clk_disable_unprepare(priv->clk);
	return 0;
}