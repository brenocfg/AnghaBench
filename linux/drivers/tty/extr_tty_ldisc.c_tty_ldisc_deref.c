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
struct tty_ldisc {TYPE_1__* tty; } ;
struct TYPE_2__ {int /*<<< orphan*/  ldisc_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ldsem_up_read (int /*<<< orphan*/ *) ; 

void tty_ldisc_deref(struct tty_ldisc *ld)
{
	ldsem_up_read(&ld->tty->ldisc_sem);
}