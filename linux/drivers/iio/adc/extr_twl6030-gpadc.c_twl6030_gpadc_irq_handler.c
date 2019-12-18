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
struct twl6030_gpadc_data {int /*<<< orphan*/  irq_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct twl6030_gpadc_data* iio_priv (void*) ; 

__attribute__((used)) static irqreturn_t twl6030_gpadc_irq_handler(int irq, void *indio_dev)
{
	struct twl6030_gpadc_data *gpadc = iio_priv(indio_dev);

	complete(&gpadc->irq_complete);

	return IRQ_HANDLED;
}