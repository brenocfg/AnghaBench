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
struct tty_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LDISC_CHANGING ; 
 int /*<<< orphan*/  TTY_LDISC_HALTED ; 
 int /*<<< orphan*/  __tty_ldisc_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void tty_ldisc_unlock(struct tty_struct *tty)
{
	clear_bit(TTY_LDISC_HALTED, &tty->flags);
	/* Can be cleared here - ldisc_unlock will wake up writers firstly */
	clear_bit(TTY_LDISC_CHANGING, &tty->flags);
	__tty_ldisc_unlock(tty);
}