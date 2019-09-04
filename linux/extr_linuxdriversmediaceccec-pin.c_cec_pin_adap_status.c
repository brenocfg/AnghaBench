#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct cec_pin {size_t state; int tx_bit; int rx_bit; int work_pin_events_dropped_cnt; int enable_irq_failed; int timer_100ms_overruns; int timer_max_overrun; int timer_sum_overrun; int rx_start_bit_low_too_short_cnt; int rx_start_bit_too_short_cnt; int rx_start_bit_too_long_cnt; int rx_data_bit_too_short_cnt; int rx_data_bit_too_long_cnt; int rx_low_drive_cnt; int tx_low_drive_cnt; TYPE_1__* ops; scalar_t__ timer_300ms_overruns; scalar_t__ timer_cnt; int /*<<< orphan*/  rx_data_bit_too_short_ts; int /*<<< orphan*/  rx_data_bit_too_short_delta; int /*<<< orphan*/  rx_start_bit_too_short_ts; int /*<<< orphan*/  rx_start_bit_too_short_delta; int /*<<< orphan*/  rx_start_bit_low_too_short_ts; int /*<<< orphan*/  rx_start_bit_low_too_short_delta; } ;
struct cec_adapter {struct cec_pin* pin; } ;
struct TYPE_4__ {int name; } ;
struct TYPE_3__ {int (* read ) (struct cec_adapter*) ;int /*<<< orphan*/  (* status ) (struct cec_adapter*,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 TYPE_2__* states ; 
 int stub1 (struct cec_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct cec_adapter*,struct seq_file*) ; 

__attribute__((used)) static void cec_pin_adap_status(struct cec_adapter *adap,
				       struct seq_file *file)
{
	struct cec_pin *pin = adap->pin;

	seq_printf(file, "state: %s\n", states[pin->state].name);
	seq_printf(file, "tx_bit: %d\n", pin->tx_bit);
	seq_printf(file, "rx_bit: %d\n", pin->rx_bit);
	seq_printf(file, "cec pin: %d\n", pin->ops->read(adap));
	seq_printf(file, "cec pin events dropped: %u\n",
		   pin->work_pin_events_dropped_cnt);
	seq_printf(file, "irq failed: %d\n", pin->enable_irq_failed);
	if (pin->timer_100ms_overruns) {
		seq_printf(file, "timer overruns > 100ms: %u of %u\n",
			   pin->timer_100ms_overruns, pin->timer_cnt);
		seq_printf(file, "timer overruns > 300ms: %u of %u\n",
			   pin->timer_300ms_overruns, pin->timer_cnt);
		seq_printf(file, "max timer overrun: %u usecs\n",
			   pin->timer_max_overrun);
		seq_printf(file, "avg timer overrun: %u usecs\n",
			   pin->timer_sum_overrun / pin->timer_100ms_overruns);
	}
	if (pin->rx_start_bit_low_too_short_cnt)
		seq_printf(file,
			   "rx start bit low too short: %u (delta %u, ts %llu)\n",
			   pin->rx_start_bit_low_too_short_cnt,
			   pin->rx_start_bit_low_too_short_delta,
			   pin->rx_start_bit_low_too_short_ts);
	if (pin->rx_start_bit_too_short_cnt)
		seq_printf(file,
			   "rx start bit too short: %u (delta %u, ts %llu)\n",
			   pin->rx_start_bit_too_short_cnt,
			   pin->rx_start_bit_too_short_delta,
			   pin->rx_start_bit_too_short_ts);
	if (pin->rx_start_bit_too_long_cnt)
		seq_printf(file, "rx start bit too long: %u\n",
			   pin->rx_start_bit_too_long_cnt);
	if (pin->rx_data_bit_too_short_cnt)
		seq_printf(file,
			   "rx data bit too short: %u (delta %u, ts %llu)\n",
			   pin->rx_data_bit_too_short_cnt,
			   pin->rx_data_bit_too_short_delta,
			   pin->rx_data_bit_too_short_ts);
	if (pin->rx_data_bit_too_long_cnt)
		seq_printf(file, "rx data bit too long: %u\n",
			   pin->rx_data_bit_too_long_cnt);
	seq_printf(file, "rx initiated low drive: %u\n", pin->rx_low_drive_cnt);
	seq_printf(file, "tx detected low drive: %u\n", pin->tx_low_drive_cnt);
	pin->work_pin_events_dropped_cnt = 0;
	pin->timer_cnt = 0;
	pin->timer_100ms_overruns = 0;
	pin->timer_300ms_overruns = 0;
	pin->timer_max_overrun = 0;
	pin->timer_sum_overrun = 0;
	pin->rx_start_bit_low_too_short_cnt = 0;
	pin->rx_start_bit_too_short_cnt = 0;
	pin->rx_start_bit_too_long_cnt = 0;
	pin->rx_data_bit_too_short_cnt = 0;
	pin->rx_data_bit_too_long_cnt = 0;
	pin->rx_low_drive_cnt = 0;
	pin->tx_low_drive_cnt = 0;
	if (pin->ops->status)
		pin->ops->status(adap, file);
}