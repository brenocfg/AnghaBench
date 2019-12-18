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
struct usb_serial_endpoints {scalar_t__ num_bulk_out; } ;
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int aircable_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	/* Ignore the first interface, which has no bulk endpoints. */
	if (epds->num_bulk_out == 0) {
		dev_dbg(&serial->interface->dev,
			"ignoring interface with no bulk-out endpoints\n");
		return -ENODEV;
	}

	return 1;
}