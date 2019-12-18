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
struct tty_struct {int /*<<< orphan*/  index; struct serial_state* driver_data; } ;
struct serial_struct {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  xmit_fifo_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  line; } ;
struct TYPE_2__ {int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; } ;
struct serial_state {int /*<<< orphan*/  custom_divisor; TYPE_1__ tport; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  xmit_fifo_size; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty, struct serial_struct *ss)
{
	struct serial_state *state = tty->driver_data;

	tty_lock(tty);
	ss->line = tty->index;
	ss->port = state->port;
	ss->flags = state->tport.flags;
	ss->xmit_fifo_size = state->xmit_fifo_size;
	ss->baud_base = state->baud_base;
	ss->close_delay = state->tport.close_delay;
	ss->closing_wait = state->tport.closing_wait;
	ss->custom_divisor = state->custom_divisor;
	tty_unlock(tty);
	return 0;
}