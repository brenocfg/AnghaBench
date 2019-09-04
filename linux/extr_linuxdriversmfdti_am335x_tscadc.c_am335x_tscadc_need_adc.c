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
typedef  int u32 ;
struct ti_tscadc_dev {int adc_waiting; int adc_in_use; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reg_se_wait; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int CHARGE_STEP ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ADCFSM ; 
 int SEQ_STATUS ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void am335x_tscadc_need_adc(struct ti_tscadc_dev *tscadc)
{
	DEFINE_WAIT(wait);
	u32 reg;

	regmap_read(tscadc->regmap, REG_ADCFSM, &reg);
	if (reg & SEQ_STATUS) {
		tscadc->adc_waiting = true;
		prepare_to_wait(&tscadc->reg_se_wait, &wait,
				TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&tscadc->reg_lock);

		schedule();

		spin_lock_irq(&tscadc->reg_lock);
		finish_wait(&tscadc->reg_se_wait, &wait);

		/*
		 * Sequencer should either be idle or
		 * busy applying the charge step.
		 */
		regmap_read(tscadc->regmap, REG_ADCFSM, &reg);
		WARN_ON((reg & SEQ_STATUS) && !(reg & CHARGE_STEP));
		tscadc->adc_waiting = false;
	}
	tscadc->adc_in_use = true;
}