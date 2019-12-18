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
struct tty_struct {int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  ctrl_status; scalar_t__ packet; struct tty_struct* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCPKT_FLUSHWRITE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_flush (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pty_flush_buffer(struct tty_struct *tty)
{
	struct tty_struct *to = tty->link;

	if (!to)
		return;

	tty_buffer_flush(to, NULL);
	if (to->packet) {
		spin_lock_irq(&tty->ctrl_lock);
		tty->ctrl_status |= TIOCPKT_FLUSHWRITE;
		wake_up_interruptible(&to->read_wait);
		spin_unlock_irq(&tty->ctrl_lock);
	}
}