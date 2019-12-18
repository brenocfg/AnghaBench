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
struct max8925_irq_data {scalar_t__ flags; int reg; int enable; int /*<<< orphan*/  tsc_irq; } ;
struct max8925_chip {scalar_t__ irq_base; struct i2c_client* i2c; struct i2c_client* adc; struct i2c_client* rtc; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct max8925_irq_data*) ; 
 scalar_t__ FLAGS_ADC ; 
 scalar_t__ FLAGS_RTC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  handle_nested_irq (scalar_t__) ; 
 struct max8925_irq_data* max8925_irqs ; 
 int max8925_reg_read (struct i2c_client*,int) ; 

__attribute__((used)) static irqreturn_t max8925_tsc_irq(int irq, void *data)
{
	struct max8925_chip *chip = data;
	struct max8925_irq_data *irq_data;
	struct i2c_client *i2c;
	int read_reg = -1, value = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(max8925_irqs); i++) {
		irq_data = &max8925_irqs[i];
		/* non TSC IRQ should be serviced in max8925_irq() */
		if (!irq_data->tsc_irq)
			continue;
		if (irq_data->flags == FLAGS_RTC)
			i2c = chip->rtc;
		else if (irq_data->flags == FLAGS_ADC)
			i2c = chip->adc;
		else
			i2c = chip->i2c;
		if (read_reg != irq_data->reg) {
			read_reg = irq_data->reg;
			value = max8925_reg_read(i2c, irq_data->reg);
		}
		if (value & irq_data->enable)
			handle_nested_irq(chip->irq_base + i);
	}
	return IRQ_HANDLED;
}