#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int frequency; unsigned int driver_data; } ;

/* Variables and functions */
 unsigned int CPUFREQ_TABLE_END ; 
#define  CPU_NEHEMIAH 129 
#define  CPU_NEHEMIAH_C 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* calc_speed (unsigned int) ; 
 int cpu_model ; 
 int /*<<< orphan*/  fsb ; 
 int /*<<< orphan*/  guess_fsb (int) ; 
 int highest_speed ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int longhaul_get_cpu_mult () ; 
 unsigned int longhaul_index ; 
 TYPE_1__* longhaul_table ; 
 int lowest_speed ; 
 int maxmult ; 
 int minmult ; 
 int* mults ; 
 int numscales ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  print_speed (int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 

__attribute__((used)) static int longhaul_get_ranges(void)
{
	unsigned int i, j, k = 0;
	unsigned int ratio;
	int mult;

	/* Get current frequency */
	mult = longhaul_get_cpu_mult();
	if (mult == -1) {
		pr_info("Invalid (reserved) multiplier!\n");
		return -EINVAL;
	}
	fsb = guess_fsb(mult);
	if (fsb == 0) {
		pr_info("Invalid (reserved) FSB!\n");
		return -EINVAL;
	}
	/* Get max multiplier - as we always did.
	 * Longhaul MSR is useful only when voltage scaling is enabled.
	 * C3 is booting at max anyway. */
	maxmult = mult;
	/* Get min multiplier */
	switch (cpu_model) {
	case CPU_NEHEMIAH:
		minmult = 50;
		break;
	case CPU_NEHEMIAH_C:
		minmult = 40;
		break;
	default:
		minmult = 30;
		break;
	}

	pr_debug("MinMult:%d.%dx MaxMult:%d.%dx\n",
		 minmult/10, minmult%10, maxmult/10, maxmult%10);

	highest_speed = calc_speed(maxmult);
	lowest_speed = calc_speed(minmult);
	pr_debug("FSB:%dMHz  Lowest speed: %s   Highest speed:%s\n", fsb,
		 print_speed(lowest_speed/1000),
		 print_speed(highest_speed/1000));

	if (lowest_speed == highest_speed) {
		pr_info("highestspeed == lowest, aborting\n");
		return -EINVAL;
	}
	if (lowest_speed > highest_speed) {
		pr_info("nonsense! lowest (%d > %d) !\n",
			lowest_speed, highest_speed);
		return -EINVAL;
	}

	longhaul_table = kcalloc(numscales + 1, sizeof(*longhaul_table),
				 GFP_KERNEL);
	if (!longhaul_table)
		return -ENOMEM;

	for (j = 0; j < numscales; j++) {
		ratio = mults[j];
		if (ratio == -1)
			continue;
		if (ratio > maxmult || ratio < minmult)
			continue;
		longhaul_table[k].frequency = calc_speed(ratio);
		longhaul_table[k].driver_data	= j;
		k++;
	}
	if (k <= 1) {
		kfree(longhaul_table);
		return -ENODEV;
	}
	/* Sort */
	for (j = 0; j < k - 1; j++) {
		unsigned int min_f, min_i;
		min_f = longhaul_table[j].frequency;
		min_i = j;
		for (i = j + 1; i < k; i++) {
			if (longhaul_table[i].frequency < min_f) {
				min_f = longhaul_table[i].frequency;
				min_i = i;
			}
		}
		if (min_i != j) {
			swap(longhaul_table[j].frequency,
			     longhaul_table[min_i].frequency);
			swap(longhaul_table[j].driver_data,
			     longhaul_table[min_i].driver_data);
		}
	}

	longhaul_table[k].frequency = CPUFREQ_TABLE_END;

	/* Find index we are running on */
	for (j = 0; j < k; j++) {
		if (mults[longhaul_table[j].driver_data & 0x1f] == mult) {
			longhaul_index = j;
			break;
		}
	}
	return 0;
}