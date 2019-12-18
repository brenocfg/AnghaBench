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
struct palmas_gpadc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  palmas_disable_auto_conversion (struct palmas_gpadc*) ; 

__attribute__((used)) static irqreturn_t palmas_gpadc_irq_auto(int irq, void *data)
{
	struct palmas_gpadc *adc = data;

	dev_dbg(adc->dev, "Threshold interrupt %d occurs\n", irq);
	palmas_disable_auto_conversion(adc);

	return IRQ_HANDLED;
}