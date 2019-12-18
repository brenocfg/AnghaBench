#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct gether {TYPE_1__* in_ep; TYPE_1__* out_ep; int /*<<< orphan*/  (* close ) (struct gether*) ;int /*<<< orphan*/  (* open ) (struct gether*) ;int /*<<< orphan*/  wrap; int /*<<< orphan*/  unwrap; int /*<<< orphan*/  header_len; int /*<<< orphan*/  is_zlp_ok; struct eth_dev* ioport; } ;
struct eth_dev {struct net_device* net; int /*<<< orphan*/  lock; struct gether* port_usb; int /*<<< orphan*/  wrap; int /*<<< orphan*/  unwrap; int /*<<< orphan*/  header_len; int /*<<< orphan*/  qmult; int /*<<< orphan*/  gadget; int /*<<< orphan*/  no_skb_reserve; int /*<<< orphan*/  zlp; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; struct eth_dev* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct eth_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int alloc_requests (struct eth_dev*,struct gether*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_start (struct eth_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gadget_avoids_skb_reserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gether*) ; 
 int /*<<< orphan*/  stub2 (struct gether*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_1__*) ; 
 int usb_ep_enable (TYPE_1__*) ; 

struct net_device *gether_connect(struct gether *link)
{
	struct eth_dev		*dev = link->ioport;
	int			result = 0;

	if (!dev)
		return ERR_PTR(-EINVAL);

	link->in_ep->driver_data = dev;
	result = usb_ep_enable(link->in_ep);
	if (result != 0) {
		DBG(dev, "enable %s --> %d\n",
			link->in_ep->name, result);
		goto fail0;
	}

	link->out_ep->driver_data = dev;
	result = usb_ep_enable(link->out_ep);
	if (result != 0) {
		DBG(dev, "enable %s --> %d\n",
			link->out_ep->name, result);
		goto fail1;
	}

	if (result == 0)
		result = alloc_requests(dev, link, qlen(dev->gadget,
					dev->qmult));

	if (result == 0) {
		dev->zlp = link->is_zlp_ok;
		dev->no_skb_reserve = gadget_avoids_skb_reserve(dev->gadget);
		DBG(dev, "qlen %d\n", qlen(dev->gadget, dev->qmult));

		dev->header_len = link->header_len;
		dev->unwrap = link->unwrap;
		dev->wrap = link->wrap;

		spin_lock(&dev->lock);
		dev->port_usb = link;
		if (netif_running(dev->net)) {
			if (link->open)
				link->open(link);
		} else {
			if (link->close)
				link->close(link);
		}
		spin_unlock(&dev->lock);

		netif_carrier_on(dev->net);
		if (netif_running(dev->net))
			eth_start(dev, GFP_ATOMIC);

	/* on error, disable any endpoints  */
	} else {
		(void) usb_ep_disable(link->out_ep);
fail1:
		(void) usb_ep_disable(link->in_ep);
	}
fail0:
	/* caller is responsible for cleanup on error */
	if (result < 0)
		return ERR_PTR(result);
	return dev->net;
}