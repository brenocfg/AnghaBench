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
struct urb {int dummy; } ;
struct sk_buff {int dummy; } ;
struct r8192_priv {TYPE_1__** rx_urb; int /*<<< orphan*/ * pp_rxskb; void* oldaddr; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int transfer_buffer_length; void* transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*) ; 
 short ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_RX_URB ; 
 int RX_URB_SIZE ; 
 int i ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short rtl8192_usb_initendpoints(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	priv->rx_urb = kmalloc_array(MAX_RX_URB + 1, sizeof(struct urb *),
				     GFP_KERNEL);
	if (!priv->rx_urb)
		return -ENOMEM;

#ifndef JACKSON_NEW_RX
	for (i = 0; i < (MAX_RX_URB + 1); i++) {
		priv->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!priv->rx_urb[i])
			return -ENOMEM;

		priv->rx_urb[i]->transfer_buffer =
			kmalloc(RX_URB_SIZE, GFP_KERNEL);
		if (!priv->rx_urb[i]->transfer_buffer)
			return -ENOMEM;

		priv->rx_urb[i]->transfer_buffer_length = RX_URB_SIZE;
	}
#endif

#ifdef THOMAS_BEACON
	{
		long align = 0;
		void *oldaddr, *newaddr;

		priv->rx_urb[16] = usb_alloc_urb(0, GFP_KERNEL);
		priv->oldaddr = kmalloc(16, GFP_KERNEL);
		if (!priv->oldaddr)
			return -ENOMEM;
		oldaddr = priv->oldaddr;
		align = ((long)oldaddr) & 3;
		if (align) {
			newaddr = oldaddr + 4 - align;
			priv->rx_urb[16]->transfer_buffer_length = 16 - 4 + align;
		} else {
			newaddr = oldaddr;
			priv->rx_urb[16]->transfer_buffer_length = 16;
		}
		priv->rx_urb[16]->transfer_buffer = newaddr;
	}
#endif

	memset(priv->rx_urb, 0, sizeof(struct urb *) * MAX_RX_URB);
	priv->pp_rxskb = kcalloc(MAX_RX_URB, sizeof(struct sk_buff *),
				 GFP_KERNEL);
	if (!priv->pp_rxskb) {
		kfree(priv->rx_urb);

		priv->pp_rxskb = NULL;
		priv->rx_urb = NULL;

		DMESGE("Endpoint Alloc Failure");
		return -ENOMEM;
	}

	netdev_dbg(dev, "End of initendpoints\n");
	return 0;
}