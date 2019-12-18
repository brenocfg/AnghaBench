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

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ irq ; 
 int /*<<< orphan*/  lock ; 
 int pcf_pending ; 
 int /*<<< orphan*/  pcf_wait ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ schedule_timeout (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void pcf_isa_waitforpin(void *data)
{
	DEFINE_WAIT(wait);
	int timeout = 2;
	unsigned long flags;

	if (irq > 0) {
		spin_lock_irqsave(&lock, flags);
		if (pcf_pending == 0) {
			spin_unlock_irqrestore(&lock, flags);
			prepare_to_wait(&pcf_wait, &wait, TASK_INTERRUPTIBLE);
			if (schedule_timeout(timeout*HZ)) {
				spin_lock_irqsave(&lock, flags);
				if (pcf_pending == 1) {
					pcf_pending = 0;
				}
				spin_unlock_irqrestore(&lock, flags);
			}
			finish_wait(&pcf_wait, &wait);
		} else {
			pcf_pending = 0;
			spin_unlock_irqrestore(&lock, flags);
		}
	} else {
		udelay(100);
	}
}