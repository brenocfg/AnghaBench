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
struct mcba_priv {int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  rx_submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcba_urb_unlink(struct mcba_priv *priv)
{
	usb_kill_anchored_urbs(&priv->rx_submitted);
	usb_kill_anchored_urbs(&priv->tx_submitted);
}