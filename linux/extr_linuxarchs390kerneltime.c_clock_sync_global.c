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
struct ptff_qto {int /*<<< orphan*/  tod_epoch_difference; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  qto ;
struct TYPE_2__ {int ts_dir; unsigned long ts_end; int /*<<< orphan*/  tb_update_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTFF_QTO ; 
 int abs (unsigned long long) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long*) ; 
 unsigned long get_tod_clock () ; 
 int /*<<< orphan*/  lpar_offset ; 
 int /*<<< orphan*/  panic (char*,unsigned long long) ; 
 scalar_t__ ptff (struct ptff_qto*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ptff_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_epoch_delta_notifier ; 
 int /*<<< orphan*/ * tod_clock_base ; 
 unsigned long long tod_steering_delta ; 
 unsigned long tod_steering_end ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* vdso_data ; 

__attribute__((used)) static void clock_sync_global(unsigned long long delta)
{
	unsigned long now, adj;
	struct ptff_qto qto;

	/* Fixup the monotonic sched clock. */
	*(unsigned long long *) &tod_clock_base[1] += delta;
	if (*(unsigned long long *) &tod_clock_base[1] < delta)
		/* Epoch overflow */
		tod_clock_base[0]++;
	/* Adjust TOD steering parameters. */
	vdso_data->tb_update_count++;
	now = get_tod_clock();
	adj = tod_steering_end - now;
	if (unlikely((s64) adj >= 0))
		/* Calculate how much of the old adjustment is left. */
		tod_steering_delta = (tod_steering_delta < 0) ?
			-(adj >> 15) : (adj >> 15);
	tod_steering_delta += delta;
	if ((abs(tod_steering_delta) >> 48) != 0)
		panic("TOD clock sync offset %lli is too large to drift\n",
		      tod_steering_delta);
	tod_steering_end = now + (abs(tod_steering_delta) << 15);
	vdso_data->ts_dir = (tod_steering_delta < 0) ? 0 : 1;
	vdso_data->ts_end = tod_steering_end;
	vdso_data->tb_update_count++;
	/* Update LPAR offset. */
	if (ptff_query(PTFF_QTO) && ptff(&qto, sizeof(qto), PTFF_QTO) == 0)
		lpar_offset = qto.tod_epoch_difference;
	/* Call the TOD clock change notifier. */
	atomic_notifier_call_chain(&s390_epoch_delta_notifier, 0, &delta);
}