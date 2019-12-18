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
struct tty_struct {struct tty_struct* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_ldisc_debug (struct tty_struct*,char*) ; 
 int /*<<< orphan*/  tty_ldisc_kill (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_lock_pair (struct tty_struct*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_unlock_pair (struct tty_struct*,struct tty_struct*) ; 

void tty_ldisc_release(struct tty_struct *tty)
{
	struct tty_struct *o_tty = tty->link;

	/*
	 * Shutdown this line discipline. As this is the final close,
	 * it does not race with the set_ldisc code path.
	 */

	tty_ldisc_lock_pair(tty, o_tty);
	tty_ldisc_kill(tty);
	if (o_tty)
		tty_ldisc_kill(o_tty);
	tty_ldisc_unlock_pair(tty, o_tty);

	/* And the memory resources remaining (buffers, termios) will be
	   disposed of when the kref hits zero */

	tty_ldisc_debug(tty, "released\n");
}