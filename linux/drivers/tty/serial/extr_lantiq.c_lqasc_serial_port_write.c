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
typedef  int /*<<< orphan*/  u_int ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lqasc_console_putchar ; 
 int /*<<< orphan*/  uart_console_write (struct uart_port*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lqasc_serial_port_write(struct uart_port *port, const char *s,
				    u_int count)
{
	uart_console_write(port, s, count, lqasc_console_putchar);
}