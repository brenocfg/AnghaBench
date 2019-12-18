#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {TYPE_1__** pp_rxskb; TYPE_1__** oldaddr; TYPE_1__** rx_urb; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__** transfer_buffer; } ;

/* Variables and functions */
 int MAX_RX_URB ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 

void rtl8192_usb_deleteendpoints(struct net_device *dev)
{
	int i;
	struct r8192_priv *priv = ieee80211_priv(dev);

#ifndef JACKSON_NEW_RX

	if (priv->rx_urb) {
		for (i = 0; i < (MAX_RX_URB + 1); i++) {
			usb_kill_urb(priv->rx_urb[i]);
			kfree(priv->rx_urb[i]->transfer_buffer);
			usb_free_urb(priv->rx_urb[i]);
		}
		kfree(priv->rx_urb);
		priv->rx_urb = NULL;
	}
#else
	kfree(priv->rx_urb);
	priv->rx_urb = NULL;
	kfree(priv->oldaddr);
	priv->oldaddr = NULL;

	kfree(priv->pp_rxskb);
	priv->pp_rxskb = 0;

#endif
}