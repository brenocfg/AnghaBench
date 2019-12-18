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
struct seq_file {int dummy; } ;

/* Variables and functions */
 unsigned long* erase_block_wear ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,...) ; 
 unsigned int wear_eb_count ; 

__attribute__((used)) static int nandsim_show(struct seq_file *m, void *private)
{
	unsigned long wmin = -1, wmax = 0, avg;
	unsigned long deciles[10], decile_max[10], tot = 0;
	unsigned int i;

	/* Calc wear stats */
	for (i = 0; i < wear_eb_count; ++i) {
		unsigned long wear = erase_block_wear[i];
		if (wear < wmin)
			wmin = wear;
		if (wear > wmax)
			wmax = wear;
		tot += wear;
	}

	for (i = 0; i < 9; ++i) {
		deciles[i] = 0;
		decile_max[i] = (wmax * (i + 1) + 5) / 10;
	}
	deciles[9] = 0;
	decile_max[9] = wmax;
	for (i = 0; i < wear_eb_count; ++i) {
		int d;
		unsigned long wear = erase_block_wear[i];
		for (d = 0; d < 10; ++d)
			if (wear <= decile_max[d]) {
				deciles[d] += 1;
				break;
			}
	}
	avg = tot / wear_eb_count;

	/* Output wear report */
	seq_printf(m, "Total numbers of erases:  %lu\n", tot);
	seq_printf(m, "Number of erase blocks:   %u\n", wear_eb_count);
	seq_printf(m, "Average number of erases: %lu\n", avg);
	seq_printf(m, "Maximum number of erases: %lu\n", wmax);
	seq_printf(m, "Minimum number of erases: %lu\n", wmin);
	for (i = 0; i < 10; ++i) {
		unsigned long from = (i ? decile_max[i - 1] + 1 : 0);
		if (from > decile_max[i])
			continue;
		seq_printf(m, "Number of ebs with erase counts from %lu to %lu : %lu\n",
			from,
			decile_max[i],
			deciles[i]);
	}

	return 0;
}