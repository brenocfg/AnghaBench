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
struct tty_port {int dummy; } ;
struct uart_state {struct tty_port port; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct serial_struct {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ uart_get_info (struct tty_port*,struct serial_struct*) ; 

__attribute__((used)) static int uart_get_info_user(struct tty_struct *tty,
			 struct serial_struct *ss)
{
	struct uart_state *state = tty->driver_data;
	struct tty_port *port = &state->port;

	return uart_get_info(port, ss) < 0 ? -EIO : 0;
}