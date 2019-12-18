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
struct uart_state {int dummy; } ;
struct uart_driver {struct uart_state* state; } ;
struct tty_struct {int index; struct uart_state* driver_data; } ;
struct tty_driver {struct uart_driver* driver_state; } ;

/* Variables and functions */
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int uart_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct uart_driver *drv = driver->driver_state;
	struct uart_state *state = drv->state + tty->index;

	tty->driver_data = state;

	return tty_standard_install(driver, tty);
}