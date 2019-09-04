#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int tp_value; } ;
struct pt_regs {int* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  linesz; } ;
struct TYPE_4__ {int /*<<< orphan*/  linesz; } ;
struct TYPE_6__ {TYPE_2__ icache; TYPE_1__ dcache; } ;

/* Variables and functions */
#define  CPU_20KC 134 
#define  CPU_25KF 133 
#define  MIPS_HWR_CC 132 
#define  MIPS_HWR_CCRES 131 
#define  MIPS_HWR_CPUNUM 130 
#define  MIPS_HWR_SYNCISTEP 129 
#define  MIPS_HWR_ULR 128 
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 int /*<<< orphan*/  current ; 
 TYPE_3__ current_cpu_data ; 
 int /*<<< orphan*/  current_cpu_type () ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int read_c0_count () ; 
 int smp_processor_id () ; 
 struct thread_info* task_thread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simulate_rdhwr(struct pt_regs *regs, int rd, int rt)
{
	struct thread_info *ti = task_thread_info(current);

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
			1, regs, 0);
	switch (rd) {
	case MIPS_HWR_CPUNUM:		/* CPU number */
		regs->regs[rt] = smp_processor_id();
		return 0;
	case MIPS_HWR_SYNCISTEP:	/* SYNCI length */
		regs->regs[rt] = min(current_cpu_data.dcache.linesz,
				     current_cpu_data.icache.linesz);
		return 0;
	case MIPS_HWR_CC:		/* Read count register */
		regs->regs[rt] = read_c0_count();
		return 0;
	case MIPS_HWR_CCRES:		/* Count register resolution */
		switch (current_cpu_type()) {
		case CPU_20KC:
		case CPU_25KF:
			regs->regs[rt] = 1;
			break;
		default:
			regs->regs[rt] = 2;
		}
		return 0;
	case MIPS_HWR_ULR:		/* Read UserLocal register */
		regs->regs[rt] = ti->tp_value;
		return 0;
	default:
		return -1;
	}
}