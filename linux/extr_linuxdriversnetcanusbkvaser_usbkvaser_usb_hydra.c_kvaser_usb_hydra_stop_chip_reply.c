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
struct kvaser_usb_net_priv {int /*<<< orphan*/  stop_comp; } ;
struct kvaser_usb {int dummy; } ;
struct kvaser_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct kvaser_usb_net_priv* kvaser_usb_hydra_net_priv_from_cmd (struct kvaser_usb const*,struct kvaser_cmd const*) ; 

__attribute__((used)) static void kvaser_usb_hydra_stop_chip_reply(const struct kvaser_usb *dev,
					     const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_net_priv *priv;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	if (!priv)
		return;

	complete(&priv->stop_comp);
}