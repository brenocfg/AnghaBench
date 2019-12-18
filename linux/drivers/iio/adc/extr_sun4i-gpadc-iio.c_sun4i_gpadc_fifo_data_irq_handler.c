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
struct sun4i_gpadc_iio {int /*<<< orphan*/  completion; int /*<<< orphan*/  adc_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ignore_fifo_data_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SUN4I_GPADC_DATA ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sun4i_gpadc_fifo_data_irq_handler(int irq, void *dev_id)
{
	struct sun4i_gpadc_iio *info = dev_id;

	if (atomic_read(&info->ignore_fifo_data_irq))
		goto out;

	if (!regmap_read(info->regmap, SUN4I_GPADC_DATA, &info->adc_data))
		complete(&info->completion);

out:
	return IRQ_HANDLED;
}