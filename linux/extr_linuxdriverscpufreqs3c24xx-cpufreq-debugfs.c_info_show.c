#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {scalar_t__ dvs; int /*<<< orphan*/  arm_divisor; int /*<<< orphan*/  p_divisor; int /*<<< orphan*/  h_divisor; } ;
struct TYPE_3__ {int /*<<< orphan*/  armclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  hclk_tns; int /*<<< orphan*/  fclk; } ;
struct s3c_cpufreq_config {int /*<<< orphan*/  lock_pll; TYPE_2__ divs; int /*<<< orphan*/  max; TYPE_1__ freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_ns (int /*<<< orphan*/ ) ; 
 struct s3c_cpufreq_config* s3c_cpufreq_getconfig () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  show_max (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int info_show(struct seq_file *seq, void *p)
{
	struct s3c_cpufreq_config *cfg;

	cfg = s3c_cpufreq_getconfig();
	if (!cfg) {
		seq_printf(seq, "no configuration registered\n");
		return 0;
	}

	seq_printf(seq, "  FCLK %ld Hz\n", cfg->freq.fclk);
	seq_printf(seq, "  HCLK %ld Hz (%lu.%lu ns)\n",
		   cfg->freq.hclk, print_ns(cfg->freq.hclk_tns));
	seq_printf(seq, "  PCLK %ld Hz\n", cfg->freq.hclk);
	seq_printf(seq, "ARMCLK %ld Hz\n", cfg->freq.armclk);
	seq_printf(seq, "\n");

	show_max(seq, &cfg->max);

	seq_printf(seq, "Divisors: P=%d, H=%d, A=%d, dvs=%s\n",
		   cfg->divs.h_divisor, cfg->divs.p_divisor,
		   cfg->divs.arm_divisor, cfg->divs.dvs ? "on" : "off");
	seq_printf(seq, "\n");

	seq_printf(seq, "lock_pll=%u\n", cfg->lock_pll);

	return 0;
}