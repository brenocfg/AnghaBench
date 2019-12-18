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
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_usb_detach (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_usb_disconnect_cb(struct brcmf_usbdev_info *devinfo)
{
	if (!devinfo)
		return;
	brcmf_dbg(USB, "Enter, bus_pub %p\n", devinfo);

	brcmf_detach(devinfo->dev);
	brcmf_free(devinfo->dev);
	kfree(devinfo->bus_pub.bus);
	brcmf_usb_detach(devinfo);
}