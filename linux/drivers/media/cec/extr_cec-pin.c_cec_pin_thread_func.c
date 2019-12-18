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
typedef  int u8 ;
struct cec_msg {int len; int* msg; int /*<<< orphan*/  rx_ts; } ;
struct cec_pin {int work_tx_status; unsigned int work_pin_events_rd; int* work_pin_events; int enable_irq_failed; int /*<<< orphan*/  timer; TYPE_1__* ops; int /*<<< orphan*/  work_irq_change; int /*<<< orphan*/  work_pin_num_events; int /*<<< orphan*/ * work_pin_ts; int /*<<< orphan*/  work_tx_ts; struct cec_msg work_rx_msg; int /*<<< orphan*/  kthread_waitq; } ;
struct cec_adapter {struct cec_pin* pin; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_irq ) (struct cec_adapter*) ;int /*<<< orphan*/  (* disable_irq ) (struct cec_adapter*) ;} ;

/* Variables and functions */
 int CEC_MAX_MSG_SIZE ; 
 unsigned int CEC_NUM_PIN_EVENTS ; 
 int CEC_PIN_EVENT_FL_DROPPED ; 
 int CEC_PIN_EVENT_FL_IS_HIGH ; 
#define  CEC_PIN_IRQ_DISABLE 129 
#define  CEC_PIN_IRQ_ENABLE 128 
 int /*<<< orphan*/  CEC_PIN_IRQ_UNCHANGED ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_pin_high (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_pin_to_idle (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_queue_pin_cec_event (struct cec_adapter*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_received_msg_ts (struct cec_adapter*,struct cec_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_transmit_attempt_done_ts (struct cec_adapter*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 scalar_t__ rx_add_byte (struct cec_pin*) ; 
 scalar_t__ rx_remove_byte (struct cec_pin*) ; 
 int /*<<< orphan*/  stub1 (struct cec_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct cec_adapter*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cec_pin_thread_func(void *_adap)
{
	struct cec_adapter *adap = _adap;
	struct cec_pin *pin = adap->pin;

	for (;;) {
		wait_event_interruptible(pin->kthread_waitq,
			kthread_should_stop() ||
			pin->work_rx_msg.len ||
			pin->work_tx_status ||
			atomic_read(&pin->work_irq_change) ||
			atomic_read(&pin->work_pin_num_events));

		if (pin->work_rx_msg.len) {
			struct cec_msg *msg = &pin->work_rx_msg;

			if (msg->len > 1 && msg->len < CEC_MAX_MSG_SIZE &&
			    rx_add_byte(pin)) {
				/* Error injection: add byte to the message */
				msg->msg[msg->len++] = 0x55;
			}
			if (msg->len > 2 && rx_remove_byte(pin)) {
				/* Error injection: remove byte from message */
				msg->len--;
			}
			if (msg->len > CEC_MAX_MSG_SIZE)
				msg->len = CEC_MAX_MSG_SIZE;
			cec_received_msg_ts(adap, msg,
				ns_to_ktime(pin->work_rx_msg.rx_ts));
			msg->len = 0;
		}
		if (pin->work_tx_status) {
			unsigned int tx_status = pin->work_tx_status;

			pin->work_tx_status = 0;
			cec_transmit_attempt_done_ts(adap, tx_status,
						     pin->work_tx_ts);
		}

		while (atomic_read(&pin->work_pin_num_events)) {
			unsigned int idx = pin->work_pin_events_rd;
			u8 v = pin->work_pin_events[idx];

			cec_queue_pin_cec_event(adap,
						v & CEC_PIN_EVENT_FL_IS_HIGH,
						v & CEC_PIN_EVENT_FL_DROPPED,
						pin->work_pin_ts[idx]);
			pin->work_pin_events_rd = (idx + 1) % CEC_NUM_PIN_EVENTS;
			atomic_dec(&pin->work_pin_num_events);
		}

		switch (atomic_xchg(&pin->work_irq_change,
				    CEC_PIN_IRQ_UNCHANGED)) {
		case CEC_PIN_IRQ_DISABLE:
			pin->ops->disable_irq(adap);
			cec_pin_high(pin);
			cec_pin_to_idle(pin);
			hrtimer_start(&pin->timer, ns_to_ktime(0),
				      HRTIMER_MODE_REL);
			break;
		case CEC_PIN_IRQ_ENABLE:
			pin->enable_irq_failed = !pin->ops->enable_irq(adap);
			if (pin->enable_irq_failed) {
				cec_pin_to_idle(pin);
				hrtimer_start(&pin->timer, ns_to_ktime(0),
					      HRTIMER_MODE_REL);
			}
			break;
		default:
			break;
		}

		if (kthread_should_stop())
			break;
	}
	return 0;
}