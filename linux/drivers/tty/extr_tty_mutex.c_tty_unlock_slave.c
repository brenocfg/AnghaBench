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
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

void tty_unlock_slave(struct tty_struct *tty)
{
	if (tty && tty != tty->link)
		tty_unlock(tty);
}