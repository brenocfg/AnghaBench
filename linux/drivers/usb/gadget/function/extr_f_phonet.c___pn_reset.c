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
struct usb_function {int dummy; } ;
struct phonet_port {int /*<<< orphan*/ * usb; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb; } ;
struct f_phonet {TYPE_1__ rx; int /*<<< orphan*/  in_ep; int /*<<< orphan*/  out_ep; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 struct phonet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pn_reset(struct usb_function *f)
{
	struct f_phonet *fp = func_to_pn(f);
	struct net_device *dev = fp->dev;
	struct phonet_port *port = netdev_priv(dev);

	netif_carrier_off(dev);
	port->usb = NULL;

	usb_ep_disable(fp->out_ep);
	usb_ep_disable(fp->in_ep);
	if (fp->rx.skb) {
		dev_kfree_skb_irq(fp->rx.skb);
		fp->rx.skb = NULL;
	}
}