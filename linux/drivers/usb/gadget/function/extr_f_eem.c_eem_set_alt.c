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
struct TYPE_6__ {int is_zlp_ok; int /*<<< orphan*/  cdc_filter; TYPE_4__* out_ep; TYPE_4__* in_ep; } ;
struct f_eem {unsigned int ctrl_id; TYPE_2__ port; } ;
struct TYPE_7__ {int /*<<< orphan*/ * desc; } ;
struct TYPE_5__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  DEFAULT_FILTER ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 scalar_t__ config_ep_by_speed (int /*<<< orphan*/ ,struct usb_function*,TYPE_4__*) ; 
 struct f_eem* func_to_eem (struct usb_function*) ; 
 struct net_device* gether_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  gether_disconnect (TYPE_2__*) ; 

__attribute__((used)) static int eem_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_eem		*eem = func_to_eem(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct net_device	*net;

	/* we know alt == 0, so this is an activation or a reset */
	if (alt != 0)
		goto fail;

	if (intf == eem->ctrl_id) {
		DBG(cdev, "reset eem\n");
		gether_disconnect(&eem->port);

		if (!eem->port.in_ep->desc || !eem->port.out_ep->desc) {
			DBG(cdev, "init eem\n");
			if (config_ep_by_speed(cdev->gadget, f,
					       eem->port.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       eem->port.out_ep)) {
				eem->port.in_ep->desc = NULL;
				eem->port.out_ep->desc = NULL;
				goto fail;
			}
		}

		/* zlps should not occur because zero-length EEM packets
		 * will be inserted in those cases where they would occur
		 */
		eem->port.is_zlp_ok = 1;
		eem->port.cdc_filter = DEFAULT_FILTER;
		DBG(cdev, "activate eem\n");
		net = gether_connect(&eem->port);
		if (IS_ERR(net))
			return PTR_ERR(net);
	} else
		goto fail;

	return 0;
fail:
	return -EINVAL;
}