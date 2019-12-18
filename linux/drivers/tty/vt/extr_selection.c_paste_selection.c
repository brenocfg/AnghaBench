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
struct vc_data {int /*<<< orphan*/  port; int /*<<< orphan*/  paste_wait; } ;
struct tty_struct {struct vc_data* driver_data; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  poke_blanked_console () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ sel_buffer ; 
 int sel_buffer_lth ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_buffer_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 unsigned int tty_ldisc_receive_buf (struct tty_ldisc*,scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 struct tty_ldisc* tty_ldisc_ref_wait (struct tty_struct*) ; 
 scalar_t__ tty_throttled (struct tty_struct*) ; 
 int /*<<< orphan*/  wait ; 

int paste_selection(struct tty_struct *tty)
{
	struct vc_data *vc = tty->driver_data;
	int	pasted = 0;
	unsigned int count;
	struct  tty_ldisc *ld;
	DECLARE_WAITQUEUE(wait, current);

	console_lock();
	poke_blanked_console();
	console_unlock();

	ld = tty_ldisc_ref_wait(tty);
	if (!ld)
		return -EIO;	/* ldisc was hung up */
	tty_buffer_lock_exclusive(&vc->port);

	add_wait_queue(&vc->paste_wait, &wait);
	while (sel_buffer && sel_buffer_lth > pasted) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (tty_throttled(tty)) {
			schedule();
			continue;
		}
		__set_current_state(TASK_RUNNING);
		count = sel_buffer_lth - pasted;
		count = tty_ldisc_receive_buf(ld, sel_buffer + pasted, NULL,
					      count);
		pasted += count;
	}
	remove_wait_queue(&vc->paste_wait, &wait);
	__set_current_state(TASK_RUNNING);

	tty_buffer_unlock_exclusive(&vc->port);
	tty_ldisc_deref(ld);
	return 0;
}