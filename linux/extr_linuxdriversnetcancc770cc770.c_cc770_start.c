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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct cc770_priv {TYPE_1__ can; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_STOPPED ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_normal_mode (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 

__attribute__((used)) static void cc770_start(struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);

	/* leave reset mode */
	if (priv->can.state != CAN_STATE_STOPPED)
		set_reset_mode(dev);

	/* leave reset mode */
	set_normal_mode(dev);
}