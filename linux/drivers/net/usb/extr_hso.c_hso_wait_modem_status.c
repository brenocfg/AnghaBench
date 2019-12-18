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
struct uart_icount {scalar_t__ rng; scalar_t__ dsr; scalar_t__ dcd; } ;
struct hso_tiocmget {int /*<<< orphan*/  waitq; int /*<<< orphan*/  icount; } ;
struct hso_serial {int /*<<< orphan*/  serial_lock; struct hso_tiocmget* tiocmget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 unsigned long TIOCM_CD ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memcpy (struct uart_icount*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
hso_wait_modem_status(struct hso_serial *serial, unsigned long arg)
{
	DECLARE_WAITQUEUE(wait, current);
	struct uart_icount cprev, cnow;
	struct hso_tiocmget  *tiocmget;
	int ret;

	tiocmget = serial->tiocmget;
	if (!tiocmget)
		return -ENOENT;
	/*
	 * note the counters on entry
	 */
	spin_lock_irq(&serial->serial_lock);
	memcpy(&cprev, &tiocmget->icount, sizeof(struct uart_icount));
	spin_unlock_irq(&serial->serial_lock);
	add_wait_queue(&tiocmget->waitq, &wait);
	for (;;) {
		spin_lock_irq(&serial->serial_lock);
		memcpy(&cnow, &tiocmget->icount, sizeof(struct uart_icount));
		spin_unlock_irq(&serial->serial_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		if (((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
		    ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
		    ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd))) {
			ret = 0;
			break;
		}
		schedule();
		/* see if a signal did it */
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
		cprev = cnow;
	}
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&tiocmget->waitq, &wait);

	return ret;
}