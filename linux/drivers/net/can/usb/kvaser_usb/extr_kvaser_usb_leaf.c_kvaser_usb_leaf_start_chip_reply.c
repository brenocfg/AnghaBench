#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct kvaser_usb_net_priv {int /*<<< orphan*/  start_comp; int /*<<< orphan*/  netdev; } ;
struct kvaser_usb {size_t nchannels; struct kvaser_usb_net_priv** nets; TYPE_3__* intf; } ;
struct TYPE_4__ {size_t channel; } ;
struct TYPE_5__ {TYPE_1__ simple; } ;
struct kvaser_cmd {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_leaf_start_chip_reply(const struct kvaser_usb *dev,
					     const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_net_priv *priv;
	u8 channel = cmd->u.simple.channel;

	if (channel >= dev->nchannels) {
		dev_err(&dev->intf->dev,
			"Invalid channel number (%d)\n", channel);
		return;
	}

	priv = dev->nets[channel];

	if (completion_done(&priv->start_comp) &&
	    netif_queue_stopped(priv->netdev)) {
		netif_wake_queue(priv->netdev);
	} else {
		netif_start_queue(priv->netdev);
		complete(&priv->start_comp);
	}
}