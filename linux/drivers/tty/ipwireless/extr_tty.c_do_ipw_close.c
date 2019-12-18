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
struct tty_struct {int /*<<< orphan*/ * driver_data; } ;
struct TYPE_2__ {scalar_t__ count; struct tty_struct* tty; } ;
struct ipw_tty {scalar_t__ tty_type; int /*<<< orphan*/  network; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ TTYTYPE_MODEM ; 
 int /*<<< orphan*/  ipwireless_ppp_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_ipw_close(struct ipw_tty *tty)
{
	tty->port.count--;

	if (tty->port.count == 0) {
		struct tty_struct *linux_tty = tty->port.tty;

		if (linux_tty != NULL) {
			tty->port.tty = NULL;
			linux_tty->driver_data = NULL;

			if (tty->tty_type == TTYTYPE_MODEM)
				ipwireless_ppp_close(tty->network);
		}
	}
}