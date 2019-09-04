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
struct xenkbd_info {int gref; int irq; int /*<<< orphan*/  page; } ;
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  devicetype; int /*<<< orphan*/  otherend_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XENKBD_FIELD_EVT_CHANNEL ; 
 int /*<<< orphan*/  XENKBD_FIELD_RING_GREF ; 
 int /*<<< orphan*/  XENKBD_FIELD_RING_REF ; 
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int bind_evtchn_to_irqhandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xenkbd_info*) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (int,int /*<<< orphan*/ ,unsigned long) ; 
 int gnttab_grant_foreign_access (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenkbd_info*) ; 
 int virt_to_gfn (int /*<<< orphan*/ ) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (struct xenbus_device*,int) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 

__attribute__((used)) static int xenkbd_connect_backend(struct xenbus_device *dev,
				  struct xenkbd_info *info)
{
	int ret, evtchn;
	struct xenbus_transaction xbt;

	ret = gnttab_grant_foreign_access(dev->otherend_id,
	                                  virt_to_gfn(info->page), 0);
	if (ret < 0)
		return ret;
	info->gref = ret;

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	if (ret)
		goto error_grant;
	ret = bind_evtchn_to_irqhandler(evtchn, input_handler,
					0, dev->devicetype, info);
	if (ret < 0) {
		xenbus_dev_fatal(dev, ret, "bind_evtchn_to_irqhandler");
		goto error_evtchan;
	}
	info->irq = ret;

 again:
	ret = xenbus_transaction_start(&xbt);
	if (ret) {
		xenbus_dev_fatal(dev, ret, "starting transaction");
		goto error_irqh;
	}
	ret = xenbus_printf(xbt, dev->nodename, XENKBD_FIELD_RING_REF, "%lu",
			    virt_to_gfn(info->page));
	if (ret)
		goto error_xenbus;
	ret = xenbus_printf(xbt, dev->nodename, XENKBD_FIELD_RING_GREF,
			    "%u", info->gref);
	if (ret)
		goto error_xenbus;
	ret = xenbus_printf(xbt, dev->nodename, XENKBD_FIELD_EVT_CHANNEL, "%u",
			    evtchn);
	if (ret)
		goto error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	if (ret) {
		if (ret == -EAGAIN)
			goto again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		goto error_irqh;
	}

	xenbus_switch_state(dev, XenbusStateInitialised);
	return 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 error_irqh:
	unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
 error_evtchan:
	xenbus_free_evtchn(dev, evtchn);
 error_grant:
	gnttab_end_foreign_access(info->gref, 0, 0UL);
	info->gref = -1;
	return ret;
}