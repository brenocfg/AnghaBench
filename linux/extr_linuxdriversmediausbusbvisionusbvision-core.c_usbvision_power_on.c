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
struct usb_usbvision {size_t dev_model; int power; } ;
struct TYPE_2__ {scalar_t__ codec; } ;

/* Variables and functions */
 scalar_t__ CODEC_WEBCAM ; 
 int /*<<< orphan*/  DBG_FUNC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int USBVISION_16_422_SYNC ; 
 int USBVISION_HVALID_PO ; 
 int USBVISION_KEEP_BLANK ; 
 int USBVISION_NOHVALID ; 
 int /*<<< orphan*/  USBVISION_PWR_REG ; 
 int USBVISION_PWR_VID ; 
 int USBVISION_RES2 ; 
 int USBVISION_SSPND_EN ; 
 int /*<<< orphan*/  USBVISION_VIN_REG1 ; 
 int /*<<< orphan*/  USBVISION_VIN_REG2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* usbvision_device_data ; 
 int usbvision_write_reg (struct usb_usbvision*,int /*<<< orphan*/ ,int) ; 

int usbvision_power_on(struct usb_usbvision *usbvision)
{
	int err_code = 0;

	PDEBUG(DBG_FUNC, "");

	usbvision_write_reg(usbvision, USBVISION_PWR_REG, USBVISION_SSPND_EN);
	usbvision_write_reg(usbvision, USBVISION_PWR_REG,
			USBVISION_SSPND_EN | USBVISION_RES2);

	if (usbvision_device_data[usbvision->dev_model].codec == CODEC_WEBCAM) {
		usbvision_write_reg(usbvision, USBVISION_VIN_REG1,
				USBVISION_16_422_SYNC | USBVISION_HVALID_PO);
		usbvision_write_reg(usbvision, USBVISION_VIN_REG2,
				USBVISION_NOHVALID | USBVISION_KEEP_BLANK);
	}
	usbvision_write_reg(usbvision, USBVISION_PWR_REG,
			USBVISION_SSPND_EN | USBVISION_PWR_VID);
	mdelay(10);
	err_code = usbvision_write_reg(usbvision, USBVISION_PWR_REG,
			USBVISION_SSPND_EN | USBVISION_PWR_VID | USBVISION_RES2);
	if (err_code == 1)
		usbvision->power = 1;
	PDEBUG(DBG_FUNC, "%s: err_code %d", (err_code < 0) ? "ERROR" : "power is on", err_code);
	return err_code;
}