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
struct tty_struct {int /*<<< orphan*/  termios; struct gsm_dlci* driver_data; } ;
struct ktermios {int dummy; } ;
struct gsm_dlci {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DLCI_CLOSED ; 
 int /*<<< orphan*/  tty_termios_copy_hw (int /*<<< orphan*/ *,struct ktermios*) ; 

__attribute__((used)) static void gsmtty_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct gsm_dlci *dlci = tty->driver_data;
	if (dlci->state == DLCI_CLOSED)
		return;
	/* For the moment its fixed. In actual fact the speed information
	   for the virtual channel can be propogated in both directions by
	   the RPN control message. This however rapidly gets nasty as we
	   then have to remap modem signals each way according to whether
	   our virtual cable is null modem etc .. */
	tty_termios_copy_hw(&tty->termios, old);
}