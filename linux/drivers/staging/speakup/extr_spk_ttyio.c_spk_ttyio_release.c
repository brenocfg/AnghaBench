#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* close ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* speakup_tty ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kclose (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_unlock (TYPE_2__*) ; 

void spk_ttyio_release(void)
{
	if (!speakup_tty)
		return;

	tty_lock(speakup_tty);

	if (speakup_tty->ops->close)
		speakup_tty->ops->close(speakup_tty, NULL);

	tty_ldisc_flush(speakup_tty);
	tty_unlock(speakup_tty);
	tty_kclose(speakup_tty);
}