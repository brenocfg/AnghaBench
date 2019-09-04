#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; int /*<<< orphan*/  mult; TYPE_3__* clock; int /*<<< orphan*/  shift; int /*<<< orphan*/  xtime_nsec; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timekeeper {TYPE_4__ tkr_mono; TYPE_1__ wall_to_monotonic; int /*<<< orphan*/  xtime_sec; } ;
struct TYPE_12__ {scalar_t__ clock_mode; int /*<<< orphan*/  cs_mask; int /*<<< orphan*/  cs_cycle_last; int /*<<< orphan*/  cs_mult; int /*<<< orphan*/  cs_shift; int /*<<< orphan*/  wall_to_mono_nsec; int /*<<< orphan*/  wall_to_mono_sec; int /*<<< orphan*/  xtime_nsec; int /*<<< orphan*/  xtime_sec; } ;
struct TYPE_9__ {scalar_t__ vdso_clock_mode; } ;
struct TYPE_10__ {TYPE_2__ archdata; } ;

/* Variables and functions */
 scalar_t__ VDSO_CLOCK_NONE ; 
 TYPE_5__ vdso_data ; 
 int /*<<< orphan*/  vdso_data_write_begin (TYPE_5__*) ; 
 int /*<<< orphan*/  vdso_data_write_end (TYPE_5__*) ; 

void update_vsyscall(struct timekeeper *tk)
{
	vdso_data_write_begin(&vdso_data);

	vdso_data.xtime_sec = tk->xtime_sec;
	vdso_data.xtime_nsec = tk->tkr_mono.xtime_nsec;
	vdso_data.wall_to_mono_sec = tk->wall_to_monotonic.tv_sec;
	vdso_data.wall_to_mono_nsec = tk->wall_to_monotonic.tv_nsec;
	vdso_data.cs_shift = tk->tkr_mono.shift;

	vdso_data.clock_mode = tk->tkr_mono.clock->archdata.vdso_clock_mode;
	if (vdso_data.clock_mode != VDSO_CLOCK_NONE) {
		vdso_data.cs_mult = tk->tkr_mono.mult;
		vdso_data.cs_cycle_last = tk->tkr_mono.cycle_last;
		vdso_data.cs_mask = tk->tkr_mono.mask;
	}

	vdso_data_write_end(&vdso_data);
}