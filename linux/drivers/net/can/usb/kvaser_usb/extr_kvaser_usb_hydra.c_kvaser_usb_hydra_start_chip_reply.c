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
struct kvaser_usb_net_priv {int /*<<< orphan*/  start_comp; int /*<<< orphan*/  netdev; } ;
struct kvaser_usb {int dummy; } ;
struct kvaser_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 struct kvaser_usb_net_priv* kvaser_usb_hydra_net_priv_from_cmd (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_hydra_start_chip_reply(const struct kvaser_usb *dev,
					      const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_net_priv *priv;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	if (!priv)
		return;

	if (completion_done(&priv->start_comp) &&
	    netif_queue_stopped(priv->netdev)) {
		netif_wake_queue(priv->netdev);
	} else {
		netif_start_queue(priv->netdev);
		complete(&priv->start_comp);
	}
}