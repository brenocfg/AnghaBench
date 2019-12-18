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
struct usb_gadget_driver {int dummy; } ;
struct usb_gadget {int /*<<< orphan*/  ep0; } ;
struct usb_composite_driver {int (* bind ) (struct usb_composite_dev*) ;int /*<<< orphan*/  name; scalar_t__ needs_serial; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  iSerialNumber; } ;
struct usb_composite_dev {TYPE_1__ desc; scalar_t__ use_os_string; int /*<<< orphan*/  gstrings; int /*<<< orphan*/  configs; struct usb_gadget* gadget; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARNING (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  __composite_unbind (struct usb_gadget*,int) ; 
 int composite_dev_prepare (struct usb_composite_driver*,struct usb_composite_dev*) ; 
 int composite_os_desc_req_prepare (struct usb_composite_dev*,int /*<<< orphan*/ ) ; 
 struct usb_composite_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gadget_data (struct usb_gadget*,struct usb_composite_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct usb_composite_dev*) ; 
 struct usb_composite_driver* to_cdriver (struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  update_unchanged_dev_desc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int composite_bind(struct usb_gadget *gadget,
		struct usb_gadget_driver *gdriver)
{
	struct usb_composite_dev	*cdev;
	struct usb_composite_driver	*composite = to_cdriver(gdriver);
	int				status = -ENOMEM;

	cdev = kzalloc(sizeof *cdev, GFP_KERNEL);
	if (!cdev)
		return status;

	spin_lock_init(&cdev->lock);
	cdev->gadget = gadget;
	set_gadget_data(gadget, cdev);
	INIT_LIST_HEAD(&cdev->configs);
	INIT_LIST_HEAD(&cdev->gstrings);

	status = composite_dev_prepare(composite, cdev);
	if (status)
		goto fail;

	/* composite gadget needs to assign strings for whole device (like
	 * serial number), register function drivers, potentially update
	 * power state and consumption, etc
	 */
	status = composite->bind(cdev);
	if (status < 0)
		goto fail;

	if (cdev->use_os_string) {
		status = composite_os_desc_req_prepare(cdev, gadget->ep0);
		if (status)
			goto fail;
	}

	update_unchanged_dev_desc(&cdev->desc, composite->dev);

	/* has userspace failed to provide a serial number? */
	if (composite->needs_serial && !cdev->desc.iSerialNumber)
		WARNING(cdev, "userspace failed to provide iSerialNumber\n");

	INFO(cdev, "%s ready\n", composite->name);
	return 0;

fail:
	__composite_unbind(gadget, false);
	return status;
}