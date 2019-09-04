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
struct tegra_emc {unsigned int num_timings; struct emc_timing* timings; } ;
struct seq_file {struct tegra_emc* private; } ;
struct emc_timing {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int emc_debug_supported_rates_show(struct seq_file *s, void *data)
{
	struct tegra_emc *emc = s->private;
	const char *prefix = "";
	unsigned int i;

	for (i = 0; i < emc->num_timings; i++) {
		struct emc_timing *timing = &emc->timings[i];

		seq_printf(s, "%s%lu", prefix, timing->rate);

		prefix = " ";
	}

	seq_puts(s, "\n");

	return 0;
}