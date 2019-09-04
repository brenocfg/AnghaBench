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
struct da9052_tsi {int /*<<< orphan*/  ts_pen_work; int /*<<< orphan*/  da9052; int /*<<< orphan*/  stopped; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_PENDOWN ; 
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  da9052_disable_irq_nosync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_enable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_ts_adc_toggle (struct da9052_tsi*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t da9052_ts_pendwn_irq(int irq, void *data)
{
	struct da9052_tsi *tsi = data;

	if (!tsi->stopped) {
		/* Mask PEN_DOWN event and unmask TSI_READY event */
		da9052_disable_irq_nosync(tsi->da9052, DA9052_IRQ_PENDOWN);
		da9052_enable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);

		da9052_ts_adc_toggle(tsi, true);

		schedule_delayed_work(&tsi->ts_pen_work, HZ / 50);
	}

	return IRQ_HANDLED;
}