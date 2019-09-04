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
struct cpuidle_driver {int safe_state_index; } ;
struct cpuidle_device {int /*<<< orphan*/  cpu; struct cpuidle_coupled* coupled; } ;
struct cpuidle_coupled {int online_count; int /*<<< orphan*/  abort_barrier; scalar_t__ prevent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cpuidle_coupled_any_pokes_pending (struct cpuidle_coupled*) ; 
 scalar_t__ cpuidle_coupled_clear_pokes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuidle_coupled_cpus_ready (struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_cpus_waiting (struct cpuidle_coupled*) ; 
 int cpuidle_coupled_get_state (struct cpuidle_device*,struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_no_cpus_ready (struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_parallel_barrier (struct cpuidle_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuidle_coupled_poke_others (int /*<<< orphan*/ ,struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_poked ; 
 int /*<<< orphan*/  cpuidle_coupled_set_done (int /*<<< orphan*/ ,struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_set_not_ready (struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_set_not_waiting (int /*<<< orphan*/ ,struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_set_ready (struct cpuidle_coupled*) ; 
 int cpuidle_coupled_set_waiting (int /*<<< orphan*/ ,struct cpuidle_coupled*,int) ; 
 int cpuidle_enter_state (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

int cpuidle_enter_state_coupled(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int next_state)
{
	int entered_state = -1;
	struct cpuidle_coupled *coupled = dev->coupled;
	int w;

	if (!coupled)
		return -EINVAL;

	while (coupled->prevent) {
		cpuidle_coupled_clear_pokes(dev->cpu);
		if (need_resched()) {
			local_irq_enable();
			return entered_state;
		}
		entered_state = cpuidle_enter_state(dev, drv,
			drv->safe_state_index);
		local_irq_disable();
	}

	/* Read barrier ensures online_count is read after prevent is cleared */
	smp_rmb();

reset:
	cpumask_clear_cpu(dev->cpu, &cpuidle_coupled_poked);

	w = cpuidle_coupled_set_waiting(dev->cpu, coupled, next_state);
	/*
	 * If this is the last cpu to enter the waiting state, poke
	 * all the other cpus out of their waiting state so they can
	 * enter a deeper state.  This can race with one of the cpus
	 * exiting the waiting state due to an interrupt and
	 * decrementing waiting_count, see comment below.
	 */
	if (w == coupled->online_count) {
		cpumask_set_cpu(dev->cpu, &cpuidle_coupled_poked);
		cpuidle_coupled_poke_others(dev->cpu, coupled);
	}

retry:
	/*
	 * Wait for all coupled cpus to be idle, using the deepest state
	 * allowed for a single cpu.  If this was not the poking cpu, wait
	 * for at least one poke before leaving to avoid a race where
	 * two cpus could arrive at the waiting loop at the same time,
	 * but the first of the two to arrive could skip the loop without
	 * processing the pokes from the last to arrive.
	 */
	while (!cpuidle_coupled_cpus_waiting(coupled) ||
			!cpumask_test_cpu(dev->cpu, &cpuidle_coupled_poked)) {
		if (cpuidle_coupled_clear_pokes(dev->cpu))
			continue;

		if (need_resched()) {
			cpuidle_coupled_set_not_waiting(dev->cpu, coupled);
			goto out;
		}

		if (coupled->prevent) {
			cpuidle_coupled_set_not_waiting(dev->cpu, coupled);
			goto out;
		}

		entered_state = cpuidle_enter_state(dev, drv,
			drv->safe_state_index);
		local_irq_disable();
	}

	cpuidle_coupled_clear_pokes(dev->cpu);
	if (need_resched()) {
		cpuidle_coupled_set_not_waiting(dev->cpu, coupled);
		goto out;
	}

	/*
	 * Make sure final poke status for this cpu is visible before setting
	 * cpu as ready.
	 */
	smp_wmb();

	/*
	 * All coupled cpus are probably idle.  There is a small chance that
	 * one of the other cpus just became active.  Increment the ready count,
	 * and spin until all coupled cpus have incremented the counter. Once a
	 * cpu has incremented the ready counter, it cannot abort idle and must
	 * spin until either all cpus have incremented the ready counter, or
	 * another cpu leaves idle and decrements the waiting counter.
	 */

	cpuidle_coupled_set_ready(coupled);
	while (!cpuidle_coupled_cpus_ready(coupled)) {
		/* Check if any other cpus bailed out of idle. */
		if (!cpuidle_coupled_cpus_waiting(coupled))
			if (!cpuidle_coupled_set_not_ready(coupled))
				goto retry;

		cpu_relax();
	}

	/*
	 * Make sure read of all cpus ready is done before reading pending pokes
	 */
	smp_rmb();

	/*
	 * There is a small chance that a cpu left and reentered idle after this
	 * cpu saw that all cpus were waiting.  The cpu that reentered idle will
	 * have sent this cpu a poke, which will still be pending after the
	 * ready loop.  The pending interrupt may be lost by the interrupt
	 * controller when entering the deep idle state.  It's not possible to
	 * clear a pending interrupt without turning interrupts on and handling
	 * it, and it's too late to turn on interrupts here, so reset the
	 * coupled idle state of all cpus and retry.
	 */
	if (cpuidle_coupled_any_pokes_pending(coupled)) {
		cpuidle_coupled_set_done(dev->cpu, coupled);
		/* Wait for all cpus to see the pending pokes */
		cpuidle_coupled_parallel_barrier(dev, &coupled->abort_barrier);
		goto reset;
	}

	/* all cpus have acked the coupled state */
	next_state = cpuidle_coupled_get_state(dev, coupled);

	entered_state = cpuidle_enter_state(dev, drv, next_state);

	cpuidle_coupled_set_done(dev->cpu, coupled);

out:
	/*
	 * Normal cpuidle states are expected to return with irqs enabled.
	 * That leads to an inefficiency where a cpu receiving an interrupt
	 * that brings it out of idle will process that interrupt before
	 * exiting the idle enter function and decrementing ready_count.  All
	 * other cpus will need to spin waiting for the cpu that is processing
	 * the interrupt.  If the driver returns with interrupts disabled,
	 * all other cpus will loop back into the safe idle state instead of
	 * spinning, saving power.
	 *
	 * Calling local_irq_enable here allows coupled states to return with
	 * interrupts disabled, but won't cause problems for drivers that
	 * exit with interrupts enabled.
	 */
	local_irq_enable();

	/*
	 * Wait until all coupled cpus have exited idle.  There is no risk that
	 * a cpu exits and re-enters the ready state because this cpu has
	 * already decremented its waiting_count.
	 */
	while (!cpuidle_coupled_no_cpus_ready(coupled))
		cpu_relax();

	return entered_state;
}