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
struct tty_struct {int /*<<< orphan*/  termios_rwsem; scalar_t__ link; int /*<<< orphan*/  disc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tty_kick_worker (struct tty_struct*) ; 
 int /*<<< orphan*/  n_tty_packet_mode_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  reset_buffer_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_tty_flush_buffer(struct tty_struct *tty)
{
	down_write(&tty->termios_rwsem);
	reset_buffer_flags(tty->disc_data);
	n_tty_kick_worker(tty);

	if (tty->link)
		n_tty_packet_mode_flush(tty);
	up_write(&tty->termios_rwsem);
}