#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct timespec64 {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct TYPE_11__ {int /*<<< orphan*/  ts_real; } ;
struct ptp_clock_event {int index; int /*<<< orphan*/  type; void* timestamp; TYPE_4__ pps_times; } ;
struct TYPE_9__ {int pin; int /*<<< orphan*/  time_stamp; } ;
struct TYPE_10__ {TYPE_2__ pps; } ;
struct mlx5_eqe {TYPE_3__ data; } ;
struct TYPE_13__ {int* start; int /*<<< orphan*/  out_work; int /*<<< orphan*/  enabled; } ;
struct TYPE_12__ {int shift; int /*<<< orphan*/  mult; } ;
struct TYPE_14__ {TYPE_1__* pin_config; } ;
struct mlx5_clock {int /*<<< orphan*/  lock; TYPE_6__ pps_info; TYPE_5__ cycles; int /*<<< orphan*/  tc; TYPE_7__ ptp_info; int /*<<< orphan*/  ptp; } ;
struct mlx5_core_dev {struct mlx5_clock clock; } ;
typedef  int s64 ;
struct TYPE_8__ {int func; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CLOCK_EXTTS ; 
 int /*<<< orphan*/  PTP_CLOCK_PPSUSR ; 
#define  PTP_PF_EXTTS 129 
#define  PTP_PF_PEROUT 128 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int div64_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_ptp_gettime (TYPE_7__*,struct timespec64*) ; 
 int mlx5_read_internal_timer (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  ns_to_timespec64 (void*) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 void* timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 
 int timespec64_to_ns (struct timespec64*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx5_pps_event(struct mlx5_core_dev *mdev,
		    struct mlx5_eqe *eqe)
{
	struct mlx5_clock *clock = &mdev->clock;
	struct ptp_clock_event ptp_event;
	struct timespec64 ts;
	u64 nsec_now, nsec_delta;
	u64 cycles_now, cycles_delta;
	int pin = eqe->data.pps.pin;
	s64 ns;
	unsigned long flags;

	switch (clock->ptp_info.pin_config[pin].func) {
	case PTP_PF_EXTTS:
		ptp_event.index = pin;
		ptp_event.timestamp = timecounter_cyc2time(&clock->tc,
					be64_to_cpu(eqe->data.pps.time_stamp));
		if (clock->pps_info.enabled) {
			ptp_event.type = PTP_CLOCK_PPSUSR;
			ptp_event.pps_times.ts_real =
					ns_to_timespec64(ptp_event.timestamp);
		} else {
			ptp_event.type = PTP_CLOCK_EXTTS;
		}
		ptp_clock_event(clock->ptp, &ptp_event);
		break;
	case PTP_PF_PEROUT:
		mlx5_ptp_gettime(&clock->ptp_info, &ts);
		cycles_now = mlx5_read_internal_timer(mdev);
		ts.tv_sec += 1;
		ts.tv_nsec = 0;
		ns = timespec64_to_ns(&ts);
		write_lock_irqsave(&clock->lock, flags);
		nsec_now = timecounter_cyc2time(&clock->tc, cycles_now);
		nsec_delta = ns - nsec_now;
		cycles_delta = div64_u64(nsec_delta << clock->cycles.shift,
					 clock->cycles.mult);
		clock->pps_info.start[pin] = cycles_now + cycles_delta;
		schedule_work(&clock->pps_info.out_work);
		write_unlock_irqrestore(&clock->lock, flags);
		break;
	default:
		mlx5_core_err(mdev, " Unhandled event\n");
	}
}