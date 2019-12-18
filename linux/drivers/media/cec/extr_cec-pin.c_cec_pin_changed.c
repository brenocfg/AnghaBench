#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cec_pin {int /*<<< orphan*/  work_irq_change; } ;
struct cec_adapter {scalar_t__ monitor_all_cnt; scalar_t__ is_configured; scalar_t__ is_configuring; struct cec_pin* pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PIN_IRQ_DISABLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_pin_update (struct cec_pin*,int,int) ; 

void cec_pin_changed(struct cec_adapter *adap, bool value)
{
	struct cec_pin *pin = adap->pin;

	cec_pin_update(pin, value, false);
	if (!value && (adap->is_configuring || adap->is_configured ||
		       adap->monitor_all_cnt))
		atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_DISABLE);
}