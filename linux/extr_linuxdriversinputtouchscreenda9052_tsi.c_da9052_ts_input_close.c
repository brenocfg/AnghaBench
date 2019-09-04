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
struct input_dev {int dummy; } ;
struct da9052_tsi {int stopped; int /*<<< orphan*/  da9052; scalar_t__ adc_on; int /*<<< orphan*/  ts_pen_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_PENDOWN ; 
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int /*<<< orphan*/  DA9052_TSI_CONT_A_REG ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da9052_disable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_enable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_ts_adc_toggle (struct da9052_tsi*,int) ; 
 struct da9052_tsi* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void da9052_ts_input_close(struct input_dev *input_dev)
{
	struct da9052_tsi *tsi = input_get_drvdata(input_dev);

	tsi->stopped = true;
	mb();
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	cancel_delayed_work_sync(&tsi->ts_pen_work);

	if (tsi->adc_on) {
		da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);
		da9052_ts_adc_toggle(tsi, false);

		/*
		 * If ADC was on that means that pendwn IRQ was disabled
		 * twice and we need to enable it to keep enable/disable
		 * counter balanced. IRQ is still off though.
		 */
		da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	}

	/* Disable Pen Detect Circuit */
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 1, 0);
}