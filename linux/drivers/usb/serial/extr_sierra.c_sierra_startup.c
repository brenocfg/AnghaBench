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
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct sierra_intf_private {int /*<<< orphan*/  susp_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sierra_intf_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nmea ; 
 int /*<<< orphan*/  sierra_set_power_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sierra_vsc_set_nmea (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,struct sierra_intf_private*) ; 

__attribute__((used)) static int sierra_startup(struct usb_serial *serial)
{
	struct sierra_intf_private *intfdata;

	intfdata = kzalloc(sizeof(*intfdata), GFP_KERNEL);
	if (!intfdata)
		return -ENOMEM;

	spin_lock_init(&intfdata->susp_lock);

	usb_set_serial_data(serial, intfdata);

	/* Set Device mode to D0 */
	sierra_set_power_state(serial->dev, 0x0000);

	/* Check NMEA and set */
	if (nmea)
		sierra_vsc_set_nmea(serial->dev, 1);

	return 0;
}