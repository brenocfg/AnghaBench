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
struct can_berr_counter {int dummy; } ;
struct kvaser_usb_net_priv {struct can_berr_counter bec; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_CHIP_STATE_REQ ; 
 int kvaser_usb_hydra_send_simple_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvaser_usb_net_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int kvaser_usb_hydra_get_berr_counter(const struct net_device *netdev,
					     struct can_berr_counter *bec)
{
	struct kvaser_usb_net_priv *priv = netdev_priv(netdev);
	int err;

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev,
					       CMD_GET_CHIP_STATE_REQ,
					       priv->channel);
	if (err)
		return err;

	*bec = priv->bec;

	return 0;
}