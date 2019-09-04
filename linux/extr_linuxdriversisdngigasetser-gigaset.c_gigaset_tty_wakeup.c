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
struct cardstate {int /*<<< orphan*/  write_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cardstate* cs_get (struct tty_struct*) ; 
 int /*<<< orphan*/  cs_put (struct cardstate*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gigaset_tty_wakeup(struct tty_struct *tty)
{
	struct cardstate *cs = cs_get(tty);

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	if (!cs)
		return;
	tasklet_schedule(&cs->write_tasklet);
	cs_put(cs);
}