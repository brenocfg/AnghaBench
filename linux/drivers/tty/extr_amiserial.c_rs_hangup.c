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
struct tty_struct {int /*<<< orphan*/  name; struct serial_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * tty; scalar_t__ count; } ;
struct serial_state {TYPE_1__ tport; } ;

/* Variables and functions */
 int /*<<< orphan*/  rs_flush_buffer (struct tty_struct*) ; 
 scalar_t__ serial_paranoia_check (struct serial_state*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (struct tty_struct*,struct serial_state*) ; 
 int /*<<< orphan*/  tty_port_set_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_hangup(struct tty_struct *tty)
{
	struct serial_state *info = tty->driver_data;

	if (serial_paranoia_check(info, tty->name, "rs_hangup"))
		return;

	rs_flush_buffer(tty);
	shutdown(tty, info);
	info->tport.count = 0;
	tty_port_set_active(&info->tport, 0);
	info->tport.tty = NULL;
	wake_up_interruptible(&info->tport.open_wait);
}