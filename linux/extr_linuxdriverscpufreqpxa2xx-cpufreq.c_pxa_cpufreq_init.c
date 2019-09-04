#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pxa_freqs {int dummy; } ;
struct TYPE_7__ {int transition_latency; } ;
struct cpufreq_policy {struct cpufreq_frequency_table* freq_table; TYPE_1__ cpuinfo; } ;
struct cpufreq_frequency_table {unsigned int frequency; int driver_data; } ;
struct TYPE_12__ {int driver_data; void* frequency; } ;
struct TYPE_11__ {void* khz; } ;
struct TYPE_10__ {int driver_data; void* frequency; } ;
struct TYPE_9__ {void* khz; } ;
struct TYPE_8__ {unsigned int khz; } ;

/* Variables and functions */
 void* CPUFREQ_TABLE_END ; 
 int NUM_PXA25x_RUN_FREQS ; 
 int NUM_PXA25x_TURBO_FREQS ; 
 int NUM_PXA27x_FREQS ; 
 scalar_t__ cpu_is_pxa25x () ; 
 scalar_t__ cpu_is_pxa27x () ; 
 int /*<<< orphan*/  find_freq_tables (struct cpufreq_frequency_table**,struct pxa_freqs const**) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 TYPE_6__* pxa255_run_freq_table ; 
 TYPE_5__* pxa255_run_freqs ; 
 TYPE_4__* pxa255_turbo_freq_table ; 
 TYPE_3__* pxa255_turbo_freqs ; 
 int pxa255_turbo_table ; 
 struct cpufreq_frequency_table* pxa27x_freq_table ; 
 TYPE_2__* pxa27x_freqs ; 
 int /*<<< orphan*/  pxa27x_guess_max_freq () ; 
 unsigned int pxa27x_maxfreq ; 
 int /*<<< orphan*/  pxa_cpufreq_init_voltages () ; 

__attribute__((used)) static int pxa_cpufreq_init(struct cpufreq_policy *policy)
{
	int i;
	unsigned int freq;
	struct cpufreq_frequency_table *pxa255_freq_table;
	const struct pxa_freqs *pxa255_freqs;

	/* try to guess pxa27x cpu */
	if (cpu_is_pxa27x())
		pxa27x_guess_max_freq();

	pxa_cpufreq_init_voltages();

	/* set default policy and cpuinfo */
	policy->cpuinfo.transition_latency = 1000; /* FIXME: 1 ms, assumed */

	/* Generate pxa25x the run cpufreq_frequency_table struct */
	for (i = 0; i < NUM_PXA25x_RUN_FREQS; i++) {
		pxa255_run_freq_table[i].frequency = pxa255_run_freqs[i].khz;
		pxa255_run_freq_table[i].driver_data = i;
	}
	pxa255_run_freq_table[i].frequency = CPUFREQ_TABLE_END;

	/* Generate pxa25x the turbo cpufreq_frequency_table struct */
	for (i = 0; i < NUM_PXA25x_TURBO_FREQS; i++) {
		pxa255_turbo_freq_table[i].frequency =
			pxa255_turbo_freqs[i].khz;
		pxa255_turbo_freq_table[i].driver_data = i;
	}
	pxa255_turbo_freq_table[i].frequency = CPUFREQ_TABLE_END;

	pxa255_turbo_table = !!pxa255_turbo_table;

	/* Generate the pxa27x cpufreq_frequency_table struct */
	for (i = 0; i < NUM_PXA27x_FREQS; i++) {
		freq = pxa27x_freqs[i].khz;
		if (freq > pxa27x_maxfreq)
			break;
		pxa27x_freq_table[i].frequency = freq;
		pxa27x_freq_table[i].driver_data = i;
	}
	pxa27x_freq_table[i].driver_data = i;
	pxa27x_freq_table[i].frequency = CPUFREQ_TABLE_END;

	/*
	 * Set the policy's minimum and maximum frequencies from the tables
	 * just constructed.  This sets cpuinfo.mxx_freq, min and max.
	 */
	if (cpu_is_pxa25x()) {
		find_freq_tables(&pxa255_freq_table, &pxa255_freqs);
		pr_info("using %s frequency table\n",
			pxa255_turbo_table ? "turbo" : "run");

		policy->freq_table = pxa255_freq_table;
	}
	else if (cpu_is_pxa27x()) {
		policy->freq_table = pxa27x_freq_table;
	}

	pr_info("frequency change support initialized\n");

	return 0;
}