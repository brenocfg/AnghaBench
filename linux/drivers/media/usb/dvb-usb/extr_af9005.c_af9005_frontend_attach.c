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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct dvb_usb_adapter {TYPE_2__* dev; TYPE_1__* fe_adap; } ;
struct TYPE_5__ {struct usb_device* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  af9005_fe_attach (TYPE_2__*) ; 
 int /*<<< orphan*/  af9005_read_eeprom (TYPE_2__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (char*)) ; 
 scalar_t__ dvb_usb_af9005_dump_eeprom ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  usb_clear_halt (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int af9005_frontend_attach(struct dvb_usb_adapter *adap)
{
	u8 buf[8];
	int i;

	/* without these calls the first commands after downloading
	   the firmware fail. I put these calls here to simulate
	   what it is done in dvb-usb-init.c.
	 */
	struct usb_device *udev = adap->dev->udev;
	usb_clear_halt(udev, usb_sndbulkpipe(udev, 2));
	usb_clear_halt(udev, usb_rcvbulkpipe(udev, 1));
	if (dvb_usb_af9005_dump_eeprom) {
		printk("EEPROM DUMP\n");
		for (i = 0; i < 255; i += 8) {
			af9005_read_eeprom(adap->dev, i, buf, 8);
			debug_dump(buf, 8, printk);
		}
	}
	adap->fe_adap[0].fe = af9005_fe_attach(adap->dev);
	return 0;
}