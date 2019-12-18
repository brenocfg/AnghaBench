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
struct xenfb_info {int irq; int /*<<< orphan*/  page; } ;
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  devicetype; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XEN_IO_PROTO_ABI_NATIVE ; 
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int bind_evtchn_to_irqhandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xenfb_info*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenfb_info*) ; 
 int /*<<< orphan*/  virt_to_gfn (int /*<<< orphan*/ ) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (struct xenbus_device*,int) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 
 int /*<<< orphan*/  xenfb_event_handler ; 

__attribute__((used)) static int xenfb_connect_backend(struct xenbus_device *dev,
				 struct xenfb_info *info)
{
	int ret, evtchn, irq;
	struct xenbus_transaction xbt;

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	if (ret)
		return ret;
	irq = bind_evtchn_to_irqhandler(evtchn, xenfb_event_handler,
					0, dev->devicetype, info);
	if (irq < 0) {
		xenbus_free_evtchn(dev, evtchn);
		xenbus_dev_fatal(dev, ret, "bind_evtchn_to_irqhandler");
		return irq;
	}
 again:
	ret = xenbus_transaction_start(&xbt);
	if (ret) {
		xenbus_dev_fatal(dev, ret, "starting transaction");
		goto unbind_irq;
	}
	ret = xenbus_printf(xbt, dev->nodename, "page-ref", "%lu",
			    virt_to_gfn(info->page));
	if (ret)
		goto error_xenbus;
	ret = xenbus_printf(xbt, dev->nodename, "event-channel", "%u",
			    evtchn);
	if (ret)
		goto error_xenbus;
	ret = xenbus_printf(xbt, dev->nodename, "protocol", "%s",
			    XEN_IO_PROTO_ABI_NATIVE);
	if (ret)
		goto error_xenbus;
	ret = xenbus_printf(xbt, dev->nodename, "feature-update", "1");
	if (ret)
		goto error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	if (ret) {
		if (ret == -EAGAIN)
			goto again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		goto unbind_irq;
	}

	xenbus_switch_state(dev, XenbusStateInitialised);
	info->irq = irq;
	return 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 unbind_irq:
	unbind_from_irqhandler(irq, info);
	return ret;
}