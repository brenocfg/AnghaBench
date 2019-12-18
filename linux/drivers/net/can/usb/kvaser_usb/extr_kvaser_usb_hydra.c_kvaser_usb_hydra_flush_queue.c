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
struct kvaser_usb_net_priv {int /*<<< orphan*/  flush_comp; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FLUSH_QUEUE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KVASER_USB_TIMEOUT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kvaser_usb_hydra_send_simple_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_usb_hydra_flush_queue(struct kvaser_usb_net_priv *priv)
{
	int err;

	init_completion(&priv->flush_comp);

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev, CMD_FLUSH_QUEUE,
					       priv->channel);
	if (err)
		return err;

	if (!wait_for_completion_timeout(&priv->flush_comp,
					 msecs_to_jiffies(KVASER_USB_TIMEOUT)))
		return -ETIMEDOUT;

	return 0;
}