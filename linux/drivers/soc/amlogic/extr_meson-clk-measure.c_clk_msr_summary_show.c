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
struct seq_file {struct meson_msr_id* private; } ;
struct meson_msr_id {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CLK_MSR_MAX ; 
 int meson_measure_best_id (struct meson_msr_id*,unsigned int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int clk_msr_summary_show(struct seq_file *s, void *data)
{
	struct meson_msr_id *msr_table = s->private;
	unsigned int precision = 0;
	int val, i;

	seq_puts(s, "  clock                     rate    precision\n");
	seq_puts(s, "---------------------------------------------\n");

	for (i = 0 ; i < CLK_MSR_MAX ; ++i) {
		if (!msr_table[i].name)
			continue;

		val = meson_measure_best_id(&msr_table[i], &precision);
		if (val < 0)
			return val;

		seq_printf(s, " %-20s %10d    +/-%dHz\n",
			   msr_table[i].name, val, precision);
	}

	return 0;
}