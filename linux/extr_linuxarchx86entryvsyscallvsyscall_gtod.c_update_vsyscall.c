#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vsyscall_gtod_data {int vclock_mode; int shift; int wall_time_snsec; int monotonic_time_snsec; long wall_time_coarse_nsec; scalar_t__ monotonic_time_coarse_nsec; scalar_t__ monotonic_time_coarse_sec; scalar_t__ wall_time_coarse_sec; scalar_t__ monotonic_time_sec; scalar_t__ wall_time_sec; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; } ;
struct TYPE_8__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {int shift; int xtime_nsec; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; TYPE_2__* clock; } ;
struct timekeeper {TYPE_4__ wall_to_monotonic; TYPE_3__ tkr_mono; scalar_t__ xtime_sec; } ;
struct TYPE_5__ {int vclock_mode; } ;
struct TYPE_6__ {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ NSEC_PER_SEC ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int VCLOCK_MAX ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtod_write_begin (struct vsyscall_gtod_data*) ; 
 int /*<<< orphan*/  gtod_write_end (struct vsyscall_gtod_data*) ; 
 int /*<<< orphan*/  vclocks_used ; 
 struct vsyscall_gtod_data vsyscall_gtod_data ; 

void update_vsyscall(struct timekeeper *tk)
{
	int vclock_mode = tk->tkr_mono.clock->archdata.vclock_mode;
	struct vsyscall_gtod_data *vdata = &vsyscall_gtod_data;

	/* Mark the new vclock used. */
	BUILD_BUG_ON(VCLOCK_MAX >= 32);
	WRITE_ONCE(vclocks_used, READ_ONCE(vclocks_used) | (1 << vclock_mode));

	gtod_write_begin(vdata);

	/* copy vsyscall data */
	vdata->vclock_mode	= vclock_mode;
	vdata->cycle_last	= tk->tkr_mono.cycle_last;
	vdata->mask		= tk->tkr_mono.mask;
	vdata->mult		= tk->tkr_mono.mult;
	vdata->shift		= tk->tkr_mono.shift;

	vdata->wall_time_sec		= tk->xtime_sec;
	vdata->wall_time_snsec		= tk->tkr_mono.xtime_nsec;

	vdata->monotonic_time_sec	= tk->xtime_sec
					+ tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_time_snsec	= tk->tkr_mono.xtime_nsec
					+ ((u64)tk->wall_to_monotonic.tv_nsec
						<< tk->tkr_mono.shift);
	while (vdata->monotonic_time_snsec >=
					(((u64)NSEC_PER_SEC) << tk->tkr_mono.shift)) {
		vdata->monotonic_time_snsec -=
					((u64)NSEC_PER_SEC) << tk->tkr_mono.shift;
		vdata->monotonic_time_sec++;
	}

	vdata->wall_time_coarse_sec	= tk->xtime_sec;
	vdata->wall_time_coarse_nsec	= (long)(tk->tkr_mono.xtime_nsec >>
						 tk->tkr_mono.shift);

	vdata->monotonic_time_coarse_sec =
		vdata->wall_time_coarse_sec + tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_time_coarse_nsec =
		vdata->wall_time_coarse_nsec + tk->wall_to_monotonic.tv_nsec;

	while (vdata->monotonic_time_coarse_nsec >= NSEC_PER_SEC) {
		vdata->monotonic_time_coarse_nsec -= NSEC_PER_SEC;
		vdata->monotonic_time_coarse_sec++;
	}

	gtod_write_end(vdata);
}