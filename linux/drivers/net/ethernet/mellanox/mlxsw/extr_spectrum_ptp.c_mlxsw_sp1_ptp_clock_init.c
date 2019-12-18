#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  mult; int /*<<< orphan*/  shift; int /*<<< orphan*/  read; } ;
struct mlxsw_sp_ptp_clock {int /*<<< orphan*/  overflow_work; int /*<<< orphan*/  ptp; int /*<<< orphan*/  ptp_info; int /*<<< orphan*/  overflow_period; TYPE_1__ cycles; int /*<<< orphan*/  tc; int /*<<< orphan*/  core; int /*<<< orphan*/  nominal_c_mult; int /*<<< orphan*/  lock; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct mlxsw_sp_ptp_clock* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP1_PTP_CLOCK_CYCLES_SHIFT ; 
 int /*<<< orphan*/  MLXSW_SP1_PTP_CLOCK_FREQ_KHZ ; 
 int /*<<< orphan*/  MLXSW_SP1_PTP_CLOCK_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clocksource_khz2mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyclecounter_cyc2ns (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  div64_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ptp_clock*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_ptp_clock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_clock_info ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_clock_overflow ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_read_frc ; 
 int /*<<< orphan*/  nsecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_register (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_ptp_clock *
mlxsw_sp1_ptp_clock_init(struct mlxsw_sp *mlxsw_sp, struct device *dev)
{
	u64 overflow_cycles, nsec, frac = 0;
	struct mlxsw_sp_ptp_clock *clock;
	int err;

	clock = kzalloc(sizeof(*clock), GFP_KERNEL);
	if (!clock)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&clock->lock);
	clock->cycles.read = mlxsw_sp1_ptp_read_frc;
	clock->cycles.shift = MLXSW_SP1_PTP_CLOCK_CYCLES_SHIFT;
	clock->cycles.mult = clocksource_khz2mult(MLXSW_SP1_PTP_CLOCK_FREQ_KHZ,
						  clock->cycles.shift);
	clock->nominal_c_mult = clock->cycles.mult;
	clock->cycles.mask = CLOCKSOURCE_MASK(MLXSW_SP1_PTP_CLOCK_MASK);
	clock->core = mlxsw_sp->core;

	timecounter_init(&clock->tc, &clock->cycles,
			 ktime_to_ns(ktime_get_real()));

	/* Calculate period in seconds to call the overflow watchdog - to make
	 * sure counter is checked at least twice every wrap around.
	 * The period is calculated as the minimum between max HW cycles count
	 * (The clock source mask) and max amount of cycles that can be
	 * multiplied by clock multiplier where the result doesn't exceed
	 * 64bits.
	 */
	overflow_cycles = div64_u64(~0ULL >> 1, clock->cycles.mult);
	overflow_cycles = min(overflow_cycles, div_u64(clock->cycles.mask, 3));

	nsec = cyclecounter_cyc2ns(&clock->cycles, overflow_cycles, 0, &frac);
	clock->overflow_period = nsecs_to_jiffies(nsec);

	INIT_DELAYED_WORK(&clock->overflow_work, mlxsw_sp1_ptp_clock_overflow);
	mlxsw_core_schedule_dw(&clock->overflow_work, 0);

	clock->ptp_info = mlxsw_sp1_ptp_clock_info;
	clock->ptp = ptp_clock_register(&clock->ptp_info, dev);
	if (IS_ERR(clock->ptp)) {
		err = PTR_ERR(clock->ptp);
		dev_err(dev, "ptp_clock_register failed %d\n", err);
		goto err_ptp_clock_register;
	}

	return clock;

err_ptp_clock_register:
	cancel_delayed_work_sync(&clock->overflow_work);
	kfree(clock);
	return ERR_PTR(err);
}