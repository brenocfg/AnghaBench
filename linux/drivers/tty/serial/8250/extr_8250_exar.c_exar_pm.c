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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_EXAR_SLEEP ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void exar_pm(struct uart_port *port, unsigned int state, unsigned int old)
{
	/*
	 * Exar UARTs have a SLEEP register that enables or disables each UART
	 * to enter sleep mode separately. On the XR17V35x the register
	 * is accessible to each UART at the UART_EXAR_SLEEP offset, but
	 * the UART channel may only write to the corresponding bit.
	 */
	serial_port_out(port, UART_EXAR_SLEEP, state ? 0xff : 0);
}