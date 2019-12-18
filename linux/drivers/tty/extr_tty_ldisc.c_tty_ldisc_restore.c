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
struct tty_struct {int dummy; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_NULL ; 
 int /*<<< orphan*/  N_TTY ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 scalar_t__ tty_ldisc_failto (struct tty_struct*,int /*<<< orphan*/ ) ; 
 char* tty_name (struct tty_struct*) ; 

__attribute__((used)) static void tty_ldisc_restore(struct tty_struct *tty, struct tty_ldisc *old)
{
	/* There is an outstanding reference here so this is safe */
	if (tty_ldisc_failto(tty, old->ops->num) < 0) {
		const char *name = tty_name(tty);

		pr_warn("Falling back ldisc for %s.\n", name);
		/* The traditional behaviour is to fall back to N_TTY, we
		   want to avoid falling back to N_NULL unless we have no
		   choice to avoid the risk of breaking anything */
		if (tty_ldisc_failto(tty, N_TTY) < 0 &&
		    tty_ldisc_failto(tty, N_NULL) < 0)
			panic("Couldn't open N_NULL ldisc for %s.", name);
	}
}