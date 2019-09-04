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
struct gtm_timer {int requested; } ;
struct gtm {int /*<<< orphan*/  lock; struct gtm_timer* timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct gtm_timer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct gtm_timer *gtm_get_specific_timer16(struct gtm *gtm,
					   unsigned int timer)
{
	struct gtm_timer *ret = ERR_PTR(-EBUSY);

	if (timer > 3)
		return ERR_PTR(-EINVAL);

	spin_lock_irq(&gtm->lock);

	if (gtm->timers[timer].requested)
		goto out;

	ret = &gtm->timers[timer];
	ret->requested = true;

out:
	spin_unlock_irq(&gtm->lock);
	return ret;
}