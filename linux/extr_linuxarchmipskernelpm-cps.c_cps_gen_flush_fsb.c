#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {int dummy; } ;
struct uasm_label {int dummy; } ;
struct TYPE_2__ {unsigned int linesz; } ;
struct cpuinfo_mips {unsigned int processor_id; int /*<<< orphan*/  cputype; TYPE_1__ dcache; } ;

/* Variables and functions */
 scalar_t__ CKSEG0 ; 
#define  CPU_INTERAPTIV 129 
#define  CPU_PROAPTIV 128 
 int /*<<< orphan*/  Hit_Invalidate_D ; 
 int /*<<< orphan*/  Hit_Writeback_Inv_SD ; 
 unsigned int PRID_REV_ENCODE_332 (int,int,int /*<<< orphan*/ ) ; 
 unsigned int PRID_REV_MASK ; 
 int /*<<< orphan*/  STYPE_SYNC ; 
 int /*<<< orphan*/  UASM_i_LA (int /*<<< orphan*/ **,int /*<<< orphan*/ ,long) ; 
 int __get_cpu_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  t2 ; 
 int /*<<< orphan*/  t3 ; 
 int /*<<< orphan*/  uasm_build_label (struct uasm_label**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uasm_i_addiu (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_ehb (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mtc0 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_sync (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_il_beqz (int /*<<< orphan*/ **,struct uasm_reloc**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zero ; 

__attribute__((used)) static int cps_gen_flush_fsb(u32 **pp, struct uasm_label **pl,
			     struct uasm_reloc **pr,
			     const struct cpuinfo_mips *cpu_info,
			     int lbl)
{
	unsigned i, fsb_size = 8;
	unsigned num_loads = (fsb_size * 3) / 2;
	unsigned line_stride = 2;
	unsigned line_size = cpu_info->dcache.linesz;
	unsigned perf_counter, perf_event;
	unsigned revision = cpu_info->processor_id & PRID_REV_MASK;

	/*
	 * Determine whether this CPU requires an FSB flush, and if so which
	 * performance counter/event reflect stalls due to a full FSB.
	 */
	switch (__get_cpu_type(cpu_info->cputype)) {
	case CPU_INTERAPTIV:
		perf_counter = 1;
		perf_event = 51;
		break;

	case CPU_PROAPTIV:
		/* Newer proAptiv cores don't require this workaround */
		if (revision >= PRID_REV_ENCODE_332(1, 1, 0))
			return 0;

		/* On older ones it's unavailable */
		return -1;

	default:
		/* Assume that the CPU does not need this workaround */
		return 0;
	}

	/*
	 * Ensure that the fill/store buffer (FSB) is not holding the results
	 * of a prefetch, since if it is then the CPC sequencer may become
	 * stuck in the D3 (ClrBus) state whilst entering a low power state.
	 */

	/* Preserve perf counter setup */
	uasm_i_mfc0(pp, t2, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uasm_i_mfc0(pp, t3, 25, (perf_counter * 2) + 1); /* PerfCntN */

	/* Setup perf counter to count FSB full pipeline stalls */
	uasm_i_addiu(pp, t0, zero, (perf_event << 5) | 0xf);
	uasm_i_mtc0(pp, t0, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uasm_i_ehb(pp);
	uasm_i_mtc0(pp, zero, 25, (perf_counter * 2) + 1); /* PerfCntN */
	uasm_i_ehb(pp);

	/* Base address for loads */
	UASM_i_LA(pp, t0, (long)CKSEG0);

	/* Start of clear loop */
	uasm_build_label(pl, *pp, lbl);

	/* Perform some loads to fill the FSB */
	for (i = 0; i < num_loads; i++)
		uasm_i_lw(pp, zero, i * line_size * line_stride, t0);

	/*
	 * Invalidate the new D-cache entries so that the cache will need
	 * refilling (via the FSB) if the loop is executed again.
	 */
	for (i = 0; i < num_loads; i++) {
		uasm_i_cache(pp, Hit_Invalidate_D,
			     i * line_size * line_stride, t0);
		uasm_i_cache(pp, Hit_Writeback_Inv_SD,
			     i * line_size * line_stride, t0);
	}

	/* Barrier ensuring previous cache invalidates are complete */
	uasm_i_sync(pp, STYPE_SYNC);
	uasm_i_ehb(pp);

	/* Check whether the pipeline stalled due to the FSB being full */
	uasm_i_mfc0(pp, t1, 25, (perf_counter * 2) + 1); /* PerfCntN */

	/* Loop if it didn't */
	uasm_il_beqz(pp, pr, t1, lbl);
	uasm_i_nop(pp);

	/* Restore perf counter 1. The count may well now be wrong... */
	uasm_i_mtc0(pp, t2, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uasm_i_ehb(pp);
	uasm_i_mtc0(pp, t3, 25, (perf_counter * 2) + 1); /* PerfCntN */
	uasm_i_ehb(pp);

	return 0;
}