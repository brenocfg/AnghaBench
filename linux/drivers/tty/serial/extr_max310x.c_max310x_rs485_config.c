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
struct serial_rs485 {int delay_rts_before_send; int delay_rts_after_send; int flags; int /*<<< orphan*/  padding; } ;
struct uart_port {struct serial_rs485 rs485; } ;
struct max310x_one {int /*<<< orphan*/  rs_work; } ;

/* Variables and functions */
 int ERANGE ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_ON_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct max310x_one* to_max310x_port (struct uart_port*) ; 

__attribute__((used)) static int max310x_rs485_config(struct uart_port *port,
				struct serial_rs485 *rs485)
{
	struct max310x_one *one = to_max310x_port(port);

	if ((rs485->delay_rts_before_send > 0x0f) ||
	    (rs485->delay_rts_after_send > 0x0f))
		return -ERANGE;

	rs485->flags &= SER_RS485_RTS_ON_SEND | SER_RS485_RX_DURING_TX |
			SER_RS485_ENABLED;
	memset(rs485->padding, 0, sizeof(rs485->padding));
	port->rs485 = *rs485;

	schedule_work(&one->rs_work);

	return 0;
}