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
struct mcba_usb_msg {int /*<<< orphan*/  cmd_id; } ;
struct mcba_usb_ctx {int dummy; } ;
struct mcba_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct mcba_usb_ctx* mcba_usb_get_free_ctx (struct mcba_priv*,int /*<<< orphan*/ *) ; 
 int mcba_usb_xmit (struct mcba_priv*,struct mcba_usb_msg*,struct mcba_usb_ctx*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcba_usb_xmit_cmd(struct mcba_priv *priv,
			      struct mcba_usb_msg *usb_msg)
{
	struct mcba_usb_ctx *ctx = NULL;
	int err;

	ctx = mcba_usb_get_free_ctx(priv, NULL);
	if (!ctx) {
		netdev_err(priv->netdev,
			   "Lack of free ctx. Sending (%d) cmd aborted",
			   usb_msg->cmd_id);

		return;
	}

	err = mcba_usb_xmit(priv, usb_msg, ctx);
	if (err)
		netdev_err(priv->netdev, "Failed to send cmd (%d)",
			   usb_msg->cmd_id);
}