#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * udc_name; } ;
struct TYPE_3__ {TYPE_2__ gadget_driver; } ;
struct gadget_info {TYPE_1__ composite; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int usb_gadget_unregister_driver (TYPE_2__*) ; 

__attribute__((used)) static int unregister_gadget(struct gadget_info *gi)
{
	int ret;

	if (!gi->composite.gadget_driver.udc_name)
		return -ENODEV;

	ret = usb_gadget_unregister_driver(&gi->composite.gadget_driver);
	if (ret)
		return ret;
	kfree(gi->composite.gadget_driver.udc_name);
	gi->composite.gadget_driver.udc_name = NULL;
	return 0;
}