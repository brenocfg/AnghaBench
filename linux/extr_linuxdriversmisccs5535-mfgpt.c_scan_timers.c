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
typedef  int uint16_t ;
struct cs5535_mfgpt_timer {int nr; struct cs5535_mfgpt_chip* chip; } ;
struct cs5535_mfgpt_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int MFGPT_MAX_TIMERS ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int MFGPT_SETUP_SETUP ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int cs5535_mfgpt_read (struct cs5535_mfgpt_timer*,int /*<<< orphan*/ ) ; 
 int mfgpt_reset_timers ; 
 int /*<<< orphan*/  reset_all_timers () ; 
 int /*<<< orphan*/  soft_reset () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int scan_timers(struct cs5535_mfgpt_chip *mfgpt)
{
	struct cs5535_mfgpt_timer timer = { .chip = mfgpt };
	unsigned long flags;
	int timers = 0;
	uint16_t val;
	int i;

	/* bios workaround */
	if (mfgpt_reset_timers == 1)
		reset_all_timers();
	else if (mfgpt_reset_timers == 2)
		soft_reset();

	/* just to be safe, protect this section w/ lock */
	spin_lock_irqsave(&mfgpt->lock, flags);
	for (i = 0; i < MFGPT_MAX_TIMERS; i++) {
		timer.nr = i;
		val = cs5535_mfgpt_read(&timer, MFGPT_REG_SETUP);
		if (!(val & MFGPT_SETUP_SETUP) || mfgpt_reset_timers == 2) {
			__set_bit(i, mfgpt->avail);
			timers++;
		}
	}
	spin_unlock_irqrestore(&mfgpt->lock, flags);

	return timers;
}