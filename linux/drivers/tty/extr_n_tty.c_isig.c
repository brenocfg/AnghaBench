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
struct tty_struct {int /*<<< orphan*/  termios_rwsem; scalar_t__ link; struct n_tty_data* disc_data; } ;
struct n_tty_data {int /*<<< orphan*/  output_lock; scalar_t__ echo_commit; scalar_t__ echo_mark; scalar_t__ echo_tail; scalar_t__ echo_head; } ;

/* Variables and functions */
 scalar_t__ L_NOFLSH (struct tty_struct*) ; 
 int /*<<< orphan*/  __isig (int,struct tty_struct*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tty_packet_mode_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  reset_buffer_flags (struct n_tty_data*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isig(int sig, struct tty_struct *tty)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (L_NOFLSH(tty)) {
		/* signal only */
		__isig(sig, tty);

	} else { /* signal and flush */
		up_read(&tty->termios_rwsem);
		down_write(&tty->termios_rwsem);

		__isig(sig, tty);

		/* clear echo buffer */
		mutex_lock(&ldata->output_lock);
		ldata->echo_head = ldata->echo_tail = 0;
		ldata->echo_mark = ldata->echo_commit = 0;
		mutex_unlock(&ldata->output_lock);

		/* clear output buffer */
		tty_driver_flush_buffer(tty);

		/* clear input buffer */
		reset_buffer_flags(tty->disc_data);

		/* notify pty master of flush */
		if (tty->link)
			n_tty_packet_mode_flush(tty);

		up_write(&tty->termios_rwsem);
		down_read(&tty->termios_rwsem);
	}
}