#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {TYPE_5__ dev; int /*<<< orphan*/  max_speed; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct dummy {TYPE_1__ gadget; } ;
struct TYPE_7__ {scalar_t__ is_high_speed; scalar_t__ is_super_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  dev_attr_function ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ *) ; 
 int device_create_file (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_ops ; 
 int /*<<< orphan*/  gadget_name ; 
 int /*<<< orphan*/  init_dummy_udc_hw (struct dummy*) ; 
 int /*<<< orphan*/  memzero_explicit (TYPE_1__*,int) ; 
 TYPE_3__ mod_data ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dummy*) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (TYPE_1__*) ; 

__attribute__((used)) static int dummy_udc_probe(struct platform_device *pdev)
{
	struct dummy	*dum;
	int		rc;

	dum = *((void **)dev_get_platdata(&pdev->dev));
	/* Clear usb_gadget region for new registration to udc-core */
	memzero_explicit(&dum->gadget, sizeof(struct usb_gadget));
	dum->gadget.name = gadget_name;
	dum->gadget.ops = &dummy_ops;
	if (mod_data.is_super_speed)
		dum->gadget.max_speed = USB_SPEED_SUPER;
	else if (mod_data.is_high_speed)
		dum->gadget.max_speed = USB_SPEED_HIGH;
	else
		dum->gadget.max_speed = USB_SPEED_FULL;

	dum->gadget.dev.parent = &pdev->dev;
	init_dummy_udc_hw(dum);

	rc = usb_add_gadget_udc(&pdev->dev, &dum->gadget);
	if (rc < 0)
		goto err_udc;

	rc = device_create_file(&dum->gadget.dev, &dev_attr_function);
	if (rc < 0)
		goto err_dev;
	platform_set_drvdata(pdev, dum);
	return rc;

err_dev:
	usb_del_gadget_udc(&dum->gadget);
err_udc:
	return rc;
}