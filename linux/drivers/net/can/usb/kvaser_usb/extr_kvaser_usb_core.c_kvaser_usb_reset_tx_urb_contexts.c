#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvaser_usb_net_priv {TYPE_2__* tx_contexts; scalar_t__ active_tx_contexts; TYPE_1__* dev; } ;
struct TYPE_4__ {int echo_index; } ;
struct TYPE_3__ {int max_tx_urbs; } ;

/* Variables and functions */

__attribute__((used)) static void kvaser_usb_reset_tx_urb_contexts(struct kvaser_usb_net_priv *priv)
{
	int i, max_tx_urbs;

	max_tx_urbs = priv->dev->max_tx_urbs;

	priv->active_tx_contexts = 0;
	for (i = 0; i < max_tx_urbs; i++)
		priv->tx_contexts[i].echo_index = max_tx_urbs;
}