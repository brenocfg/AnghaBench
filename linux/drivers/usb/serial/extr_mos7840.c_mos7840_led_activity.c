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
struct usb_serial_port {int dummy; } ;
struct moschip_port {int /*<<< orphan*/  led_timer1; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_ON_MS ; 
 int /*<<< orphan*/  MODEM_CONTROL_REGISTER ; 
 int /*<<< orphan*/  MOS7840_FLAG_LED_BUSY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mos7840_set_led_async (struct moschip_port*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct moschip_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void mos7840_led_activity(struct usb_serial_port *port)
{
	struct moschip_port *mos7840_port = usb_get_serial_port_data(port);

	if (test_and_set_bit_lock(MOS7840_FLAG_LED_BUSY, &mos7840_port->flags))
		return;

	mos7840_set_led_async(mos7840_port, 0x0301, MODEM_CONTROL_REGISTER);
	mod_timer(&mos7840_port->led_timer1,
				jiffies + msecs_to_jiffies(LED_ON_MS));
}