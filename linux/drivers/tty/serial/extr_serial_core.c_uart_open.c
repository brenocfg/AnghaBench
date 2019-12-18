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
struct uart_state {int /*<<< orphan*/  port; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int uart_open(struct tty_struct *tty, struct file *filp)
{
	struct uart_state *state = tty->driver_data;
	int retval;

	retval = tty_port_open(&state->port, tty, filp);
	if (retval > 0)
		retval = 0;

	return retval;
}