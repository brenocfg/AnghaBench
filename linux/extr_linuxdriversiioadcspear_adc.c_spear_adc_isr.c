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
struct spear_adc_state {int /*<<< orphan*/  completion; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spear_adc_get_average (struct spear_adc_state*) ; 

__attribute__((used)) static irqreturn_t spear_adc_isr(int irq, void *dev_id)
{
	struct spear_adc_state *st = dev_id;

	/* Read value to clear IRQ */
	st->value = spear_adc_get_average(st);
	complete(&st->completion);

	return IRQ_HANDLED;
}