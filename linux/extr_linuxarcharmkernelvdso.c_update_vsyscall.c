#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int xtime_nsec; int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  mult; int /*<<< orphan*/  cycle_last; } ;
struct timekeeper {TYPE_1__ tkr_mono; int /*<<< orphan*/  xtime_sec; struct timespec64 wall_to_monotonic; } ;
struct TYPE_7__ {int xtime_clock_snsec; int cs_shift; int /*<<< orphan*/  cs_mask; int /*<<< orphan*/  cs_mult; int /*<<< orphan*/  xtime_clock_sec; int /*<<< orphan*/  cs_cycle_last; scalar_t__ tk_is_cntvct; int /*<<< orphan*/  wtm_clock_nsec; int /*<<< orphan*/  wtm_clock_sec; scalar_t__ xtime_coarse_nsec; int /*<<< orphan*/  xtime_coarse_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cntvct_ok ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 scalar_t__ tk_is_cntvct (struct timekeeper*) ; 
 TYPE_2__* vdso_data ; 
 int /*<<< orphan*/  vdso_write_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  vdso_write_end (TYPE_2__*) ; 
 int /*<<< orphan*/  virt_to_page (TYPE_2__*) ; 

void update_vsyscall(struct timekeeper *tk)
{
	struct timespec64 *wtm = &tk->wall_to_monotonic;

	if (!cntvct_ok) {
		/* The entry points have been zeroed, so there is no
		 * point in updating the data page.
		 */
		return;
	}

	vdso_write_begin(vdso_data);

	vdso_data->tk_is_cntvct			= tk_is_cntvct(tk);
	vdso_data->xtime_coarse_sec		= tk->xtime_sec;
	vdso_data->xtime_coarse_nsec		= (u32)(tk->tkr_mono.xtime_nsec >>
							tk->tkr_mono.shift);
	vdso_data->wtm_clock_sec		= wtm->tv_sec;
	vdso_data->wtm_clock_nsec		= wtm->tv_nsec;

	if (vdso_data->tk_is_cntvct) {
		vdso_data->cs_cycle_last	= tk->tkr_mono.cycle_last;
		vdso_data->xtime_clock_sec	= tk->xtime_sec;
		vdso_data->xtime_clock_snsec	= tk->tkr_mono.xtime_nsec;
		vdso_data->cs_mult		= tk->tkr_mono.mult;
		vdso_data->cs_shift		= tk->tkr_mono.shift;
		vdso_data->cs_mask		= tk->tkr_mono.mask;
	}

	vdso_write_end(vdso_data);

	flush_dcache_page(virt_to_page(vdso_data));
}