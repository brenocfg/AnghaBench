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
struct usb_8dev_priv {TYPE_1__* tx_contexts; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  rx_submitted; } ;
struct TYPE_2__ {int echo_index; } ;

/* Variables and functions */
 int MAX_TX_URBS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlink_all_urbs(struct usb_8dev_priv *priv)
{
	int i;

	usb_kill_anchored_urbs(&priv->rx_submitted);

	usb_kill_anchored_urbs(&priv->tx_submitted);
	atomic_set(&priv->active_tx_urbs, 0);

	for (i = 0; i < MAX_TX_URBS; i++)
		priv->tx_contexts[i].echo_index = MAX_TX_URBS;
}