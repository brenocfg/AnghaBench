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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void serial_pxa_dl_write(struct uart_8250_port *up, int value)
{
	unsigned int dll;

	serial_out(up, UART_DLL, value & 0xff);
	/*
	 * work around Erratum #74 according to Marvel(R) PXA270M Processor
	 * Specification Update (April 19, 2010)
	 */
	dll = serial_in(up, UART_DLL);
	WARN_ON(dll != (value & 0xff));

	serial_out(up, UART_DLM, value >> 8 & 0xff);
}