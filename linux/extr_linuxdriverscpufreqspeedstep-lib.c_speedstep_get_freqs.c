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
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum speedstep_processor { ____Placeholder_speedstep_processor } speedstep_processor ;

/* Variables and functions */
 unsigned int EINVAL ; 
 unsigned int EIO ; 
 unsigned int ENODEV ; 
 unsigned int SPEEDSTEP_HIGH ; 
 unsigned int SPEEDSTEP_LOW ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned int speedstep_get_frequency (int) ; 

unsigned int speedstep_get_freqs(enum speedstep_processor processor,
				  unsigned int *low_speed,
				  unsigned int *high_speed,
				  unsigned int *transition_latency,
				  void (*set_state) (unsigned int state))
{
	unsigned int prev_speed;
	unsigned int ret = 0;
	unsigned long flags;
	ktime_t tv1, tv2;

	if ((!processor) || (!low_speed) || (!high_speed) || (!set_state))
		return -EINVAL;

	pr_debug("trying to determine both speeds\n");

	/* get current speed */
	prev_speed = speedstep_get_frequency(processor);
	if (!prev_speed)
		return -EIO;

	pr_debug("previous speed is %u\n", prev_speed);

	preempt_disable();
	local_irq_save(flags);

	/* switch to low state */
	set_state(SPEEDSTEP_LOW);
	*low_speed = speedstep_get_frequency(processor);
	if (!*low_speed) {
		ret = -EIO;
		goto out;
	}

	pr_debug("low speed is %u\n", *low_speed);

	/* start latency measurement */
	if (transition_latency)
		tv1 = ktime_get();

	/* switch to high state */
	set_state(SPEEDSTEP_HIGH);

	/* end latency measurement */
	if (transition_latency)
		tv2 = ktime_get();

	*high_speed = speedstep_get_frequency(processor);
	if (!*high_speed) {
		ret = -EIO;
		goto out;
	}

	pr_debug("high speed is %u\n", *high_speed);

	if (*low_speed == *high_speed) {
		ret = -ENODEV;
		goto out;
	}

	/* switch to previous state, if necessary */
	if (*high_speed != prev_speed)
		set_state(SPEEDSTEP_LOW);

	if (transition_latency) {
		*transition_latency = ktime_to_us(ktime_sub(tv2, tv1));
		pr_debug("transition latency is %u uSec\n", *transition_latency);

		/* convert uSec to nSec and add 20% for safety reasons */
		*transition_latency *= 1200;

		/* check if the latency measurement is too high or too low
		 * and set it to a safe value (500uSec) in that case
		 */
		if (*transition_latency > 10000000 ||
		    *transition_latency < 50000) {
			pr_warn("frequency transition measured seems out of range (%u nSec), falling back to a safe one of %u nSec\n",
				*transition_latency, 500000);
			*transition_latency = 500000;
		}
	}

out:
	local_irq_restore(flags);
	preempt_enable();

	return ret;
}