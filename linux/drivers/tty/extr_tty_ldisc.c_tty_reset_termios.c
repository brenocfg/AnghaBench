#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;
struct tty_struct {int /*<<< orphan*/  termios_rwsem; TYPE_2__ termios; TYPE_1__* driver; } ;
struct TYPE_4__ {TYPE_2__ init_termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_termios_baud_rate (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_termios_input_baud_rate (TYPE_2__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty_reset_termios(struct tty_struct *tty)
{
	down_write(&tty->termios_rwsem);
	tty->termios = tty->driver->init_termios;
	tty->termios.c_ispeed = tty_termios_input_baud_rate(&tty->termios);
	tty->termios.c_ospeed = tty_termios_baud_rate(&tty->termios);
	up_write(&tty->termios_rwsem);
}