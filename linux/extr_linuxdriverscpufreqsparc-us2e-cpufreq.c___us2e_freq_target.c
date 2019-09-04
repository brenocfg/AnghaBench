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
 int /*<<< orphan*/  HBIRD_ESTAR_MODE_ADDR ; 
 unsigned long estar_to_divisor (unsigned long) ; 
 unsigned long index_to_divisor (unsigned int) ; 
 unsigned long index_to_estar_mode (unsigned int) ; 
 unsigned long read_hbreg (int /*<<< orphan*/ ) ; 
 unsigned int smp_processor_id () ; 
 int sparc64_get_clock_tick (unsigned int) ; 
 int /*<<< orphan*/  us2e_transition (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void __us2e_freq_target(void *arg)
{
	unsigned int cpu = smp_processor_id();
	unsigned int *index = arg;
	unsigned long new_bits, new_freq;
	unsigned long clock_tick, divisor, old_divisor, estar;

	new_freq = clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	new_bits = index_to_estar_mode(*index);
	divisor = index_to_divisor(*index);
	new_freq /= divisor;

	estar = read_hbreg(HBIRD_ESTAR_MODE_ADDR);

	old_divisor = estar_to_divisor(estar);

	if (old_divisor != divisor) {
		us2e_transition(estar, new_bits, clock_tick * 1000,
				old_divisor, divisor);
	}
}