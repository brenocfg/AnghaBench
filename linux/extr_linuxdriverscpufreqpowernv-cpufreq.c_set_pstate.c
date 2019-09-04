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
struct powernv_smp_call_data {unsigned long pstate_id; unsigned long gpstate_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PMCR ; 
 unsigned long get_pmspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_pmspr (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void set_pstate(void *data)
{
	unsigned long val;
	struct powernv_smp_call_data *freq_data = data;
	unsigned long pstate_ul = freq_data->pstate_id;
	unsigned long gpstate_ul = freq_data->gpstate_id;

	val = get_pmspr(SPRN_PMCR);
	val = val & 0x0000FFFFFFFFFFFFULL;

	pstate_ul = pstate_ul & 0xFF;
	gpstate_ul = gpstate_ul & 0xFF;

	/* Set both global(bits 56..63) and local(bits 48..55) PStates */
	val = val | (gpstate_ul << 56) | (pstate_ul << 48);

	pr_debug("Setting cpu %d pmcr to %016lX\n",
			raw_smp_processor_id(), val);
	set_pmspr(SPRN_PMCR, val);
}