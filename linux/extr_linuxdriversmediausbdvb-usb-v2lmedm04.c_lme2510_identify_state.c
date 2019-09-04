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
struct lme2510_state {int /*<<< orphan*/  dvb_usb_lme2510_firmware; } ;
struct dvb_usb_device {TYPE_1__* props; int /*<<< orphan*/  udev; struct lme2510_state* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  bInterfaceNumber; } ;

/* Variables and functions */
 int COLD ; 
 int EINVAL ; 
 int WARM ; 
 int /*<<< orphan*/  dvb_usb_lme2510_firmware ; 
 int lme2510_return_status (struct dvb_usb_device*) ; 
 char* lme_firmware_switch (struct dvb_usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_configuration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lme2510_identify_state(struct dvb_usb_device *d, const char **name)
{
	struct lme2510_state *st = d->priv;
	int status;

	usb_reset_configuration(d->udev);

	usb_set_interface(d->udev,
		d->props->bInterfaceNumber, 1);

	st->dvb_usb_lme2510_firmware = dvb_usb_lme2510_firmware;

	status = lme2510_return_status(d);
	if (status == 0x44) {
		*name = lme_firmware_switch(d, 0);
		return COLD;
	}

	if (status != 0x47)
		return -EINVAL;

	return WARM;
}