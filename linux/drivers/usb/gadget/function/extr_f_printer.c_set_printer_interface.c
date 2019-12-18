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
struct printer_dev {TYPE_1__* out_ep; TYPE_1__* in_ep; int /*<<< orphan*/  gadget; } ;
struct TYPE_3__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  name; struct printer_dev* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct printer_dev*,char*,int /*<<< orphan*/ ,int) ; 
 void* ep_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_ep_in_desc ; 
 int /*<<< orphan*/  fs_ep_out_desc ; 
 int /*<<< orphan*/  hs_ep_in_desc ; 
 int /*<<< orphan*/  hs_ep_out_desc ; 
 int /*<<< orphan*/  ss_ep_in_desc ; 
 int /*<<< orphan*/  ss_ep_out_desc ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_1__*) ; 
 int usb_ep_enable (TYPE_1__*) ; 

__attribute__((used)) static int
set_printer_interface(struct printer_dev *dev)
{
	int			result = 0;

	dev->in_ep->desc = ep_desc(dev->gadget, &fs_ep_in_desc, &hs_ep_in_desc,
				&ss_ep_in_desc);
	dev->in_ep->driver_data = dev;

	dev->out_ep->desc = ep_desc(dev->gadget, &fs_ep_out_desc,
				    &hs_ep_out_desc, &ss_ep_out_desc);
	dev->out_ep->driver_data = dev;

	result = usb_ep_enable(dev->in_ep);
	if (result != 0) {
		DBG(dev, "enable %s --> %d\n", dev->in_ep->name, result);
		goto done;
	}

	result = usb_ep_enable(dev->out_ep);
	if (result != 0) {
		DBG(dev, "enable %s --> %d\n", dev->in_ep->name, result);
		goto done;
	}

done:
	/* on error, disable any endpoints  */
	if (result != 0) {
		(void) usb_ep_disable(dev->in_ep);
		(void) usb_ep_disable(dev->out_ep);
		dev->in_ep->desc = NULL;
		dev->out_ep->desc = NULL;
	}

	/* caller is responsible for cleanup on error */
	return result;
}