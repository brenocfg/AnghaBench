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
struct tty_struct {TYPE_1__* ops; scalar_t__ stopped; scalar_t__ flow_stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

void __start_tty(struct tty_struct *tty)
{
	if (!tty->stopped || tty->flow_stopped)
		return;
	tty->stopped = 0;
	if (tty->ops->start)
		tty->ops->start(tty);
	tty_wakeup(tty);
}