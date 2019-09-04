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
struct TYPE_3__ {scalar_t__ len; } ;
struct cec_pin {int enabled; int work_pin_events_dropped; int /*<<< orphan*/  state; int /*<<< orphan*/  kthread; int /*<<< orphan*/  timer; TYPE_2__* ops; int /*<<< orphan*/  work_irq_change; int /*<<< orphan*/  timer_ts; TYPE_1__ tx_msg; scalar_t__ work_pin_events_wr; scalar_t__ work_pin_events_rd; int /*<<< orphan*/  work_pin_num_events; } ;
struct cec_adapter {struct cec_pin* pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_irq ) (struct cec_adapter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PIN_IRQ_UNCHANGED ; 
 int /*<<< orphan*/  CEC_ST_OFF ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_pin_read (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_pin_thread_func ; 
 int /*<<< orphan*/  cec_pin_to_idle (struct cec_pin*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct cec_adapter*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct cec_adapter*) ; 

__attribute__((used)) static int cec_pin_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct cec_pin *pin = adap->pin;

	pin->enabled = enable;
	if (enable) {
		atomic_set(&pin->work_pin_num_events, 0);
		pin->work_pin_events_rd = pin->work_pin_events_wr = 0;
		pin->work_pin_events_dropped = false;
		cec_pin_read(pin);
		cec_pin_to_idle(pin);
		pin->tx_msg.len = 0;
		pin->timer_ts = ns_to_ktime(0);
		atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_UNCHANGED);
		pin->kthread = kthread_run(cec_pin_thread_func, adap,
					   "cec-pin");
		if (IS_ERR(pin->kthread)) {
			pr_err("cec-pin: kernel_thread() failed\n");
			return PTR_ERR(pin->kthread);
		}
		hrtimer_start(&pin->timer, ns_to_ktime(0),
			      HRTIMER_MODE_REL);
	} else {
		if (pin->ops->disable_irq)
			pin->ops->disable_irq(adap);
		hrtimer_cancel(&pin->timer);
		kthread_stop(pin->kthread);
		cec_pin_read(pin);
		cec_pin_to_idle(pin);
		pin->state = CEC_ST_OFF;
	}
	return 0;
}