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
struct uart_port {scalar_t__ line; } ;
struct console {scalar_t__ index; } ;
struct TYPE_2__ {struct console* cons; } ;

/* Variables and functions */
 TYPE_1__ sprd_uart_driver ; 

__attribute__((used)) static bool sprd_uart_is_console(struct uart_port *uport)
{
	struct console *cons = sprd_uart_driver.cons;

	if (cons && cons->index >= 0 && cons->index == uport->line)
		return true;

	return false;
}