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
struct cec_pin {scalar_t__ state; int /*<<< orphan*/  timer; int /*<<< orphan*/  adap; TYPE_1__* ops; int /*<<< orphan*/  work_irq_change; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_irq ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PIN_IRQ_UNCHANGED ; 
 scalar_t__ CEC_ST_RX_IRQ ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_pin_high (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_pin_to_idle (struct cec_pin*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void cec_pin_start_timer(struct cec_pin *pin)
{
	if (pin->state != CEC_ST_RX_IRQ)
		return;

	atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_UNCHANGED);
	pin->ops->disable_irq(pin->adap);
	cec_pin_high(pin);
	cec_pin_to_idle(pin);
	hrtimer_start(&pin->timer, ns_to_ktime(0), HRTIMER_MODE_REL);
}