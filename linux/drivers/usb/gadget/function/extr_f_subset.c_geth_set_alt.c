#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_4__* out_ep; TYPE_4__* in_ep; } ;
struct f_gether {TYPE_2__ port; } ;
struct TYPE_7__ {int /*<<< orphan*/ * desc; scalar_t__ enabled; } ;
struct TYPE_5__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int EINVAL ; 
 int PTR_ERR_OR_ZERO (struct net_device*) ; 
 scalar_t__ config_ep_by_speed (int /*<<< orphan*/ ,struct usb_function*,TYPE_4__*) ; 
 struct f_gether* func_to_geth (struct usb_function*) ; 
 struct net_device* gether_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  gether_disconnect (TYPE_2__*) ; 

__attribute__((used)) static int geth_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_gether		*geth = func_to_geth(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct net_device	*net;

	/* we know alt == 0, so this is an activation or a reset */

	if (geth->port.in_ep->enabled) {
		DBG(cdev, "reset cdc subset\n");
		gether_disconnect(&geth->port);
	}

	DBG(cdev, "init + activate cdc subset\n");
	if (config_ep_by_speed(cdev->gadget, f, geth->port.in_ep) ||
	    config_ep_by_speed(cdev->gadget, f, geth->port.out_ep)) {
		geth->port.in_ep->desc = NULL;
		geth->port.out_ep->desc = NULL;
		return -EINVAL;
	}

	net = gether_connect(&geth->port);
	return PTR_ERR_OR_ZERO(net);
}