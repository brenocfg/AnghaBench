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
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;
struct can_priv {int /*<<< orphan*/  data_bitrate_const_cnt; int /*<<< orphan*/  data_bitrate_const; int /*<<< orphan*/  bitrate_const_cnt; int /*<<< orphan*/  bitrate_const; int /*<<< orphan*/  do_set_termination; int /*<<< orphan*/  termination_const; int /*<<< orphan*/  termination_const_cnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  can_link_ops ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

int register_candev(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	/* Ensure termination_const, termination_const_cnt and
	 * do_set_termination consistency. All must be either set or
	 * unset.
	 */
	if ((!priv->termination_const != !priv->termination_const_cnt) ||
	    (!priv->termination_const != !priv->do_set_termination))
		return -EINVAL;

	if (!priv->bitrate_const != !priv->bitrate_const_cnt)
		return -EINVAL;

	if (!priv->data_bitrate_const != !priv->data_bitrate_const_cnt)
		return -EINVAL;

	dev->rtnl_link_ops = &can_link_ops;
	netif_carrier_off(dev);

	return register_netdev(dev);
}