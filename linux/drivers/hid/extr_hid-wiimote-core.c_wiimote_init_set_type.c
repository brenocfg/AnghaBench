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
struct wiimote_data {TYPE_1__* hdev; } ;
typedef  size_t __u8 ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ product; char* name; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_NINTENDO_WIIMOTE ; 
 scalar_t__ USB_DEVICE_ID_NINTENDO_WIIMOTE2 ; 
 scalar_t__ USB_VENDOR_ID_NINTENDO ; 
 size_t WIIMOTE_DEV_BALANCE_BOARD ; 
 size_t WIIMOTE_DEV_GEN10 ; 
 size_t WIIMOTE_DEV_GEN20 ; 
 size_t WIIMOTE_DEV_GENERIC ; 
 size_t WIIMOTE_DEV_PRO_CONTROLLER ; 
 size_t WIIMOTE_EXT_BALANCE_BOARD ; 
 size_t WIIMOTE_EXT_PRO_CONTROLLER ; 
 int /*<<< orphan*/  hid_info (TYPE_1__*,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * wiimote_devtype_names ; 
 int /*<<< orphan*/  wiimote_modules_load (struct wiimote_data*,size_t) ; 

__attribute__((used)) static void wiimote_init_set_type(struct wiimote_data *wdata,
				  __u8 exttype)
{
	__u8 devtype = WIIMOTE_DEV_GENERIC;
	__u16 vendor, product;
	const char *name;

	vendor = wdata->hdev->vendor;
	product = wdata->hdev->product;
	name = wdata->hdev->name;

	if (exttype == WIIMOTE_EXT_BALANCE_BOARD) {
		devtype = WIIMOTE_DEV_BALANCE_BOARD;
		goto done;
	} else if (exttype == WIIMOTE_EXT_PRO_CONTROLLER) {
		devtype = WIIMOTE_DEV_PRO_CONTROLLER;
		goto done;
	}

	if (!strcmp(name, "Nintendo RVL-CNT-01")) {
		devtype = WIIMOTE_DEV_GEN10;
		goto done;
	} else if (!strcmp(name, "Nintendo RVL-CNT-01-TR")) {
		devtype = WIIMOTE_DEV_GEN20;
		goto done;
	} else if (!strcmp(name, "Nintendo RVL-WBC-01")) {
		devtype = WIIMOTE_DEV_BALANCE_BOARD;
		goto done;
	} else if (!strcmp(name, "Nintendo RVL-CNT-01-UC")) {
		devtype = WIIMOTE_DEV_PRO_CONTROLLER;
		goto done;
	}

	if (vendor == USB_VENDOR_ID_NINTENDO) {
		if (product == USB_DEVICE_ID_NINTENDO_WIIMOTE) {
			devtype = WIIMOTE_DEV_GEN10;
			goto done;
		} else if (product == USB_DEVICE_ID_NINTENDO_WIIMOTE2) {
			devtype = WIIMOTE_DEV_GEN20;
			goto done;
		}
	}

done:
	if (devtype == WIIMOTE_DEV_GENERIC)
		hid_info(wdata->hdev, "cannot detect device; NAME: %s VID: %04x PID: %04x EXT: %04x\n",
			name, vendor, product, exttype);
	else
		hid_info(wdata->hdev, "detected device: %s\n",
			 wiimote_devtype_names[devtype]);

	wiimote_modules_load(wdata, devtype);
}