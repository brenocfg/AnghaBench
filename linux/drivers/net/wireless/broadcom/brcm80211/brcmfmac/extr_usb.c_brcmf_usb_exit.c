#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_driver {int dummy; } ;
struct TYPE_4__ {struct device_driver driver; } ;
struct TYPE_5__ {TYPE_1__ drvwrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_usb_reset_device ; 
 TYPE_2__ brcmf_usbdrvr ; 
 int driver_for_each_device (struct device_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister (TYPE_2__*) ; 

void brcmf_usb_exit(void)
{
	struct device_driver *drv = &brcmf_usbdrvr.drvwrap.driver;
	int ret;

	brcmf_dbg(USB, "Enter\n");
	ret = driver_for_each_device(drv, NULL, NULL,
				     brcmf_usb_reset_device);
	usb_deregister(&brcmf_usbdrvr);
}