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
struct cpufreq_frequency_table {int dummy; } ;
struct clk_rate_round_data {int max; unsigned long rate; struct cpufreq_frequency_table* arg; int /*<<< orphan*/  func; int /*<<< orphan*/  min; } ;
struct clk {int nr_freqs; } ;

/* Variables and functions */
 long ENOSYS ; 
 long clk_rate_round_helper (struct clk_rate_round_data*) ; 
 int /*<<< orphan*/  clk_rate_table_iter ; 

long clk_rate_table_round(struct clk *clk,
			  struct cpufreq_frequency_table *freq_table,
			  unsigned long rate)
{
	struct clk_rate_round_data table_round = {
		.min	= 0,
		.max	= clk->nr_freqs - 1,
		.func	= clk_rate_table_iter,
		.arg	= freq_table,
		.rate	= rate,
	};

	if (clk->nr_freqs < 1)
		return -ENOSYS;

	return clk_rate_round_helper(&table_round);
}