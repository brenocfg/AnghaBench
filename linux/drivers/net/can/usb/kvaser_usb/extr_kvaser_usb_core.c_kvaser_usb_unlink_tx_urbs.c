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
struct kvaser_usb_net_priv {int /*<<< orphan*/  tx_submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvaser_usb_reset_tx_urb_contexts (struct kvaser_usb_net_priv*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvaser_usb_unlink_tx_urbs(struct kvaser_usb_net_priv *priv)
{
	usb_kill_anchored_urbs(&priv->tx_submitted);
	kvaser_usb_reset_tx_urb_contexts(priv);
}