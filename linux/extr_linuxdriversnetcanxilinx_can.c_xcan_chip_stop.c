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
struct xcan_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 

__attribute__((used)) static void xcan_chip_stop(struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);

	/* Disable interrupts and leave the can in configuration mode */
	set_reset_mode(ndev);
	priv->can.state = CAN_STATE_STOPPED;
}