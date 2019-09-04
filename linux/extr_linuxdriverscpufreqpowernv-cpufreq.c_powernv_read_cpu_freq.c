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
struct powernv_smp_call_data {int /*<<< orphan*/  freq; int /*<<< orphan*/  pstate_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PMSR ; 
 int /*<<< orphan*/  extract_local_pstate (unsigned long) ; 
 unsigned long get_pmspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstate_id_to_freq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static void powernv_read_cpu_freq(void *arg)
{
	unsigned long pmspr_val;
	struct powernv_smp_call_data *freq_data = arg;

	pmspr_val = get_pmspr(SPRN_PMSR);
	freq_data->pstate_id = extract_local_pstate(pmspr_val);
	freq_data->freq = pstate_id_to_freq(freq_data->pstate_id);

	pr_debug("cpu %d pmsr %016lX pstate_id 0x%x frequency %d kHz\n",
		 raw_smp_processor_id(), pmspr_val, freq_data->pstate_id,
		 freq_data->freq);
}