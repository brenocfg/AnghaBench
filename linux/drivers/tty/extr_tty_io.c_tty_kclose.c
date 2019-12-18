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
struct tty_struct {int /*<<< orphan*/  index; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_tty (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_debug_hangup (struct tty_struct*,char*) ; 
 int /*<<< orphan*/  tty_flush_works (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_release (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_mutex ; 
 int /*<<< orphan*/  tty_port_set_kopened (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tty_kclose(struct tty_struct *tty)
{
	/*
	 * Ask the line discipline code to release its structures
	 */
	tty_ldisc_release(tty);

	/* Wait for pending work before tty destruction commmences */
	tty_flush_works(tty);

	tty_debug_hangup(tty, "freeing structure\n");
	/*
	 * The release_tty function takes care of the details of clearing
	 * the slots and preserving the termios structure. The tty_unlock_pair
	 * should be safe as we keep a kref while the tty is locked (so the
	 * unlock never unlocks a freed tty).
	 */
	mutex_lock(&tty_mutex);
	tty_port_set_kopened(tty->port, 0);
	release_tty(tty, tty->index);
	mutex_unlock(&tty_mutex);
}