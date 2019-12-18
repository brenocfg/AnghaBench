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
struct kvaser_usb_net_priv {int /*<<< orphan*/  stop_comp; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  CMD_STOP_CHIP_REQ ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KVASER_USB_TIMEOUT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kvaser_usb_hydra_send_simple_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_usb_hydra_stop_chip(struct kvaser_usb_net_priv *priv)
{
	int err;

	init_completion(&priv->stop_comp);

	/* Make sure we do not report invalid BUS_OFF from CMD_CHIP_STATE_EVENT
	 * see comment in kvaser_usb_hydra_update_state()
	 */
	priv->can.state = CAN_STATE_STOPPED;

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev, CMD_STOP_CHIP_REQ,
					       priv->channel);
	if (err)
		return err;

	if (!wait_for_completion_timeout(&priv->stop_comp,
					 msecs_to_jiffies(KVASER_USB_TIMEOUT)))
		return -ETIMEDOUT;

	return 0;
}