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
struct wm831x_dcdc {int /*<<< orphan*/  regulator; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REGULATOR_EVENT_UNDER_VOLTAGE ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_notifier_call_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm831x_dcdc_uv_irq(int irq, void *data)
{
	struct wm831x_dcdc *dcdc = data;

	regulator_lock(dcdc->regulator);
	regulator_notifier_call_chain(dcdc->regulator,
				      REGULATOR_EVENT_UNDER_VOLTAGE,
				      NULL);
	regulator_unlock(dcdc->regulator);

	return IRQ_HANDLED;
}