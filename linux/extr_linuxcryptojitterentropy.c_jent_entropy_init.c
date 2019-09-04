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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int JENT_ECOARSETIME ; 
 int JENT_EMINVARVAR ; 
 int JENT_ENOMONOTONIC ; 
 int JENT_ENOTIME ; 
 int JENT_EVARVAR ; 
 int MIN_FOLD_LOOP_BIT ; 
 int /*<<< orphan*/  jent_fold_time (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  jent_get_nstime (scalar_t__*) ; 

int jent_entropy_init(void)
{
	int i;
	__u64 delta_sum = 0;
	__u64 old_delta = 0;
	int time_backwards = 0;
	int count_var = 0;
	int count_mod = 0;

	/* We could perform statistical tests here, but the problem is
	 * that we only have a few loop counts to do testing. These
	 * loop counts may show some slight skew and we produce
	 * false positives.
	 *
	 * Moreover, only old systems show potentially problematic
	 * jitter entropy that could potentially be caught here. But
	 * the RNG is intended for hardware that is available or widely
	 * used, but not old systems that are long out of favor. Thus,
	 * no statistical tests.
	 */

	/*
	 * We could add a check for system capabilities such as clock_getres or
	 * check for CONFIG_X86_TSC, but it does not make much sense as the
	 * following sanity checks verify that we have a high-resolution
	 * timer.
	 */
	/*
	 * TESTLOOPCOUNT needs some loops to identify edge systems. 100 is
	 * definitely too little.
	 */
#define TESTLOOPCOUNT 300
#define CLEARCACHE 100
	for (i = 0; (TESTLOOPCOUNT + CLEARCACHE) > i; i++) {
		__u64 time = 0;
		__u64 time2 = 0;
		__u64 folded = 0;
		__u64 delta = 0;
		unsigned int lowdelta = 0;

		jent_get_nstime(&time);
		jent_fold_time(NULL, time, &folded, 1<<MIN_FOLD_LOOP_BIT);
		jent_get_nstime(&time2);

		/* test whether timer works */
		if (!time || !time2)
			return JENT_ENOTIME;
		delta = time2 - time;
		/*
		 * test whether timer is fine grained enough to provide
		 * delta even when called shortly after each other -- this
		 * implies that we also have a high resolution timer
		 */
		if (!delta)
			return JENT_ECOARSETIME;

		/*
		 * up to here we did not modify any variable that will be
		 * evaluated later, but we already performed some work. Thus we
		 * already have had an impact on the caches, branch prediction,
		 * etc. with the goal to clear it to get the worst case
		 * measurements.
		 */
		if (CLEARCACHE > i)
			continue;

		/* test whether we have an increasing timer */
		if (!(time2 > time))
			time_backwards++;

		/*
		 * Avoid modulo of 64 bit integer to allow code to compile
		 * on 32 bit architectures.
		 */
		lowdelta = time2 - time;
		if (!(lowdelta % 100))
			count_mod++;

		/*
		 * ensure that we have a varying delta timer which is necessary
		 * for the calculation of entropy -- perform this check
		 * only after the first loop is executed as we need to prime
		 * the old_data value
		 */
		if (i) {
			if (delta != old_delta)
				count_var++;
			if (delta > old_delta)
				delta_sum += (delta - old_delta);
			else
				delta_sum += (old_delta - delta);
		}
		old_delta = delta;
	}

	/*
	 * we allow up to three times the time running backwards.
	 * CLOCK_REALTIME is affected by adjtime and NTP operations. Thus,
	 * if such an operation just happens to interfere with our test, it
	 * should not fail. The value of 3 should cover the NTP case being
	 * performed during our test run.
	 */
	if (3 < time_backwards)
		return JENT_ENOMONOTONIC;
	/* Error if the time variances are always identical */
	if (!delta_sum)
		return JENT_EVARVAR;

	/*
	 * Variations of deltas of time must on average be larger
	 * than 1 to ensure the entropy estimation
	 * implied with 1 is preserved
	 */
	if (delta_sum <= 1)
		return JENT_EMINVARVAR;

	/*
	 * Ensure that we have variations in the time stamp below 10 for at
	 * least 10% of all checks -- on some platforms, the counter
	 * increments in multiples of 100, but not always
	 */
	if ((TESTLOOPCOUNT/10 * 9) < count_mod)
		return JENT_ECOARSETIME;

	return 0;
}