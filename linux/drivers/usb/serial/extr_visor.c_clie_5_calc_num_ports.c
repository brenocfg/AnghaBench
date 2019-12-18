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
struct usb_serial_endpoints {int /*<<< orphan*/ * bulk_out; } ;
struct usb_serial {TYPE_1__* type; } ;
struct TYPE_2__ {int num_ports; } ;

/* Variables and functions */

__attribute__((used)) static int clie_5_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	/*
	 * TH55 registers 2 ports.
	 * Communication in from the UX50/TH55 uses the first bulk-in
	 * endpoint, while communication out to the UX50/TH55 uses the second
	 * bulk-out endpoint.
	 */

	/*
	 * FIXME: Should we swap the descriptors instead of using the same
	 *        bulk-out endpoint for both ports?
	 */
	epds->bulk_out[0] = epds->bulk_out[1];

	return serial->type->num_ports;
}