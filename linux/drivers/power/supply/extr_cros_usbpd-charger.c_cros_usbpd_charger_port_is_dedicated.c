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
struct port_data {scalar_t__ port_number; TYPE_1__* charger; } ;
struct TYPE_2__ {scalar_t__ num_usbpd_ports; } ;

/* Variables and functions */

__attribute__((used)) static bool cros_usbpd_charger_port_is_dedicated(struct port_data *port)
{
	return port->port_number >= port->charger->num_usbpd_ports;
}