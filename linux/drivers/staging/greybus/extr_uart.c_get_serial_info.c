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
struct tty_struct {struct gb_tty* driver_data; } ;
struct serial_struct {int xmit_fifo_size; int baud_base; int close_delay; int closing_wait; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int close_delay; int closing_wait; } ;
struct gb_tty {TYPE_1__ port; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int ASYNC_CLOSING_WAIT_NONE ; 
 int /*<<< orphan*/  PORT_16550A ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty,
			   struct serial_struct *ss)
{
	struct gb_tty *gb_tty = tty->driver_data;

	ss->type = PORT_16550A;
	ss->line = gb_tty->minor;
	ss->xmit_fifo_size = 16;
	ss->baud_base = 9600;
	ss->close_delay = gb_tty->port.close_delay / 10;
	ss->closing_wait =
		gb_tty->port.closing_wait == ASYNC_CLOSING_WAIT_NONE ?
		ASYNC_CLOSING_WAIT_NONE : gb_tty->port.closing_wait / 10;
	return 0;
}