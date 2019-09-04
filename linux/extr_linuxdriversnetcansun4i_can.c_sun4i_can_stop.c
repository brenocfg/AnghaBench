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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct sun4ican_priv {scalar_t__ base; TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 scalar_t__ SUN4I_REG_INTEN_ADDR ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sun4ican_priv* netdev_priv (struct net_device*) ; 
 int set_reset_mode (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun4i_can_stop(struct net_device *dev)
{
	struct sun4ican_priv *priv = netdev_priv(dev);
	int err;

	priv->can.state = CAN_STATE_STOPPED;
	/* we need to enter reset mode */
	err = set_reset_mode(dev);
	if (err) {
		netdev_err(dev, "could not enter reset mode\n");
		return err;
	}

	/* disable all interrupts */
	writel(0, priv->base + SUN4I_REG_INTEN_ADDR);

	return 0;
}