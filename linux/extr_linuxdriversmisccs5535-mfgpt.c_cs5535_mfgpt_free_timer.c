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
typedef  int uint16_t ;
struct cs5535_mfgpt_timer {TYPE_1__* chip; int /*<<< orphan*/  nr; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int MFGPT_SETUP_SETUP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cs5535_mfgpt_read (struct cs5535_mfgpt_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cs5535_mfgpt_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cs5535_mfgpt_free_timer(struct cs5535_mfgpt_timer *timer)
{
	unsigned long flags;
	uint16_t val;

	/* timer can be made available again only if never set up */
	val = cs5535_mfgpt_read(timer, MFGPT_REG_SETUP);
	if (!(val & MFGPT_SETUP_SETUP)) {
		spin_lock_irqsave(&timer->chip->lock, flags);
		__set_bit(timer->nr, timer->chip->avail);
		spin_unlock_irqrestore(&timer->chip->lock, flags);
	}

	kfree(timer);
}