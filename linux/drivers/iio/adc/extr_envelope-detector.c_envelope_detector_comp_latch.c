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
struct envelope {int comp; int /*<<< orphan*/  comp_irq; int /*<<< orphan*/  comp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int envelope_detector_comp_latch(struct envelope *env)
{
	int comp;

	spin_lock_irq(&env->comp_lock);
	comp = env->comp;
	env->comp = 0;
	spin_unlock_irq(&env->comp_lock);

	if (!comp)
		return 0;

	/*
	 * The irq was disabled, and is reenabled just now.
	 * But there might have been a pending irq that
	 * happened while the irq was disabled that fires
	 * just as the irq is reenabled. That is not what
	 * is desired.
	 */
	enable_irq(env->comp_irq);

	/* So, synchronize this possibly pending irq... */
	synchronize_irq(env->comp_irq);

	/* ...and redo the whole dance. */
	spin_lock_irq(&env->comp_lock);
	comp = env->comp;
	env->comp = 0;
	spin_unlock_irq(&env->comp_lock);

	if (comp)
		enable_irq(env->comp_irq);

	return 1;
}