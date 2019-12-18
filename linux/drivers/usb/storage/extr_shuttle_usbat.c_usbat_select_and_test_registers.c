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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_ATA ; 
 int /*<<< orphan*/  USBAT_ATA_DEVICE ; 
 int /*<<< orphan*/  USBAT_ATA_LBA_HI ; 
 int /*<<< orphan*/  USBAT_ATA_LBA_ME ; 
 int /*<<< orphan*/  USBAT_ATA_STATUS ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 scalar_t__ USB_STOR_XFER_GOOD ; 
 scalar_t__ usbat_read (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ usbat_write (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbat_select_and_test_registers(struct us_data *us)
{
	int selector;
	unsigned char *status = us->iobuf;

	/* try device = master, then device = slave. */
	for (selector = 0xA0; selector <= 0xB0; selector += 0x10) {
		if (usbat_write(us, USBAT_ATA, USBAT_ATA_DEVICE, selector) !=
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_STATUS, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_DEVICE, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_HI, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_write(us, USBAT_ATA, USBAT_ATA_LBA_ME, 0x55) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_write(us, USBAT_ATA, USBAT_ATA_LBA_HI, 0xAA) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;
	}

	return USB_STOR_TRANSPORT_GOOD;
}