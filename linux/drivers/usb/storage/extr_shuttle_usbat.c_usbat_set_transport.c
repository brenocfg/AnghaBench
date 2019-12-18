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
struct usbat_info {int devicetype; } ;
struct us_data {int /*<<< orphan*/  transport; } ;

/* Variables and functions */
#define  USBAT_DEV_FLASH 129 
#define  USBAT_DEV_HP8200 128 
 int USB_STOR_TRANSPORT_ERROR ; 
 int /*<<< orphan*/  usbat_flash_transport ; 
 int /*<<< orphan*/  usbat_hp8200e_transport ; 
 int /*<<< orphan*/  usbat_identify_device (struct us_data*,struct usbat_info*) ; 

__attribute__((used)) static int usbat_set_transport(struct us_data *us,
			       struct usbat_info *info,
			       int devicetype)
{

	if (!info->devicetype)
		info->devicetype = devicetype;

	if (!info->devicetype)
		usbat_identify_device(us, info);

	switch (info->devicetype) {
	default:
		return USB_STOR_TRANSPORT_ERROR;

	case  USBAT_DEV_HP8200:
		us->transport = usbat_hp8200e_transport;
		break;

	case USBAT_DEV_FLASH:
		us->transport = usbat_flash_transport;
		break;
	}

	return 0;
}