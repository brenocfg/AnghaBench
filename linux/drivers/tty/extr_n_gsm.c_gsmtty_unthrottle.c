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
struct tty_struct {struct gsm_dlci* driver_data; } ;
struct gsm_dlci {scalar_t__ state; scalar_t__ throttled; int /*<<< orphan*/  modem_tx; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DLCI_CLOSED ; 
 int /*<<< orphan*/  TIOCM_DTR ; 
 int /*<<< orphan*/  gsmtty_modem_update (struct gsm_dlci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsmtty_unthrottle(struct tty_struct *tty)
{
	struct gsm_dlci *dlci = tty->driver_data;
	if (dlci->state == DLCI_CLOSED)
		return;
	if (C_CRTSCTS(tty))
		dlci->modem_tx |= TIOCM_DTR;
	dlci->throttled = 0;
	/* Send an MSC with DTR set */
	gsmtty_modem_update(dlci, 0);
}