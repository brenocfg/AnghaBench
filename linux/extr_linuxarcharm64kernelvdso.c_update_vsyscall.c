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
typedef  int u32 ;
struct TYPE_11__ {int xtime_nsec; int shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  cycle_last; TYPE_2__* clock; } ;
struct TYPE_10__ {int /*<<< orphan*/  mult; int /*<<< orphan*/  xtime_nsec; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timekeeper {TYPE_5__ tkr_mono; TYPE_4__ tkr_raw; int /*<<< orphan*/  xtime_sec; int /*<<< orphan*/  raw_sec; TYPE_3__ wall_to_monotonic; } ;
struct TYPE_12__ {int use_syscall; int xtime_coarse_nsec; int xtime_clock_nsec; int cs_shift; int /*<<< orphan*/  tb_seq_count; int /*<<< orphan*/  cs_raw_mult; int /*<<< orphan*/  cs_mono_mult; int /*<<< orphan*/  xtime_clock_sec; int /*<<< orphan*/  raw_time_nsec; int /*<<< orphan*/  raw_time_sec; int /*<<< orphan*/  cs_cycle_last; int /*<<< orphan*/  wtm_clock_nsec; int /*<<< orphan*/  wtm_clock_sec; int /*<<< orphan*/  xtime_coarse_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  vdso_direct; } ;
struct TYPE_8__ {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 TYPE_6__* vdso_data ; 

void update_vsyscall(struct timekeeper *tk)
{
	u32 use_syscall = !tk->tkr_mono.clock->archdata.vdso_direct;

	++vdso_data->tb_seq_count;
	smp_wmb();

	vdso_data->use_syscall			= use_syscall;
	vdso_data->xtime_coarse_sec		= tk->xtime_sec;
	vdso_data->xtime_coarse_nsec		= tk->tkr_mono.xtime_nsec >>
							tk->tkr_mono.shift;
	vdso_data->wtm_clock_sec		= tk->wall_to_monotonic.tv_sec;
	vdso_data->wtm_clock_nsec		= tk->wall_to_monotonic.tv_nsec;

	if (!use_syscall) {
		/* tkr_mono.cycle_last == tkr_raw.cycle_last */
		vdso_data->cs_cycle_last	= tk->tkr_mono.cycle_last;
		vdso_data->raw_time_sec         = tk->raw_sec;
		vdso_data->raw_time_nsec        = tk->tkr_raw.xtime_nsec;
		vdso_data->xtime_clock_sec	= tk->xtime_sec;
		vdso_data->xtime_clock_nsec	= tk->tkr_mono.xtime_nsec;
		vdso_data->cs_mono_mult		= tk->tkr_mono.mult;
		vdso_data->cs_raw_mult		= tk->tkr_raw.mult;
		/* tkr_mono.shift == tkr_raw.shift */
		vdso_data->cs_shift		= tk->tkr_mono.shift;
	}

	smp_wmb();
	++vdso_data->tb_seq_count;
}