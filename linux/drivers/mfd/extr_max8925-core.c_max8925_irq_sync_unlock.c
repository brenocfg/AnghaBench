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
struct max8925_irq_data {int mask_reg; unsigned char enable; } ;
struct max8925_chip {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  adc; int /*<<< orphan*/  rtc; int /*<<< orphan*/  i2c; int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct max8925_irq_data*) ; 
#define  MAX8925_CHG_IRQ1_MASK 133 
#define  MAX8925_CHG_IRQ2_MASK 132 
#define  MAX8925_ON_OFF_IRQ1_MASK 131 
#define  MAX8925_ON_OFF_IRQ2_MASK 130 
#define  MAX8925_RTC_IRQ_MASK 129 
#define  MAX8925_TSC_IRQ_MASK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct max8925_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct max8925_irq_data* max8925_irqs ; 
 int /*<<< orphan*/  max8925_reg_write (int /*<<< orphan*/ ,int const,unsigned char) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max8925_irq_sync_unlock(struct irq_data *data)
{
	struct max8925_chip *chip = irq_data_get_irq_chip_data(data);
	struct max8925_irq_data *irq_data;
	static unsigned char cache_chg[2] = {0xff, 0xff};
	static unsigned char cache_on[2] = {0xff, 0xff};
	static unsigned char cache_rtc = 0xff, cache_tsc = 0xff;
	unsigned char irq_chg[2], irq_on[2];
	unsigned char irq_rtc, irq_tsc;
	int i;

	/* Load cached value. In initial, all IRQs are masked */
	irq_chg[0] = cache_chg[0];
	irq_chg[1] = cache_chg[1];
	irq_on[0] = cache_on[0];
	irq_on[1] = cache_on[1];
	irq_rtc = cache_rtc;
	irq_tsc = cache_tsc;
	for (i = 0; i < ARRAY_SIZE(max8925_irqs); i++) {
		irq_data = &max8925_irqs[i];
		/* 1 -- disable, 0 -- enable */
		switch (irq_data->mask_reg) {
		case MAX8925_CHG_IRQ1_MASK:
			irq_chg[0] &= ~irq_data->enable;
			break;
		case MAX8925_CHG_IRQ2_MASK:
			irq_chg[1] &= ~irq_data->enable;
			break;
		case MAX8925_ON_OFF_IRQ1_MASK:
			irq_on[0] &= ~irq_data->enable;
			break;
		case MAX8925_ON_OFF_IRQ2_MASK:
			irq_on[1] &= ~irq_data->enable;
			break;
		case MAX8925_RTC_IRQ_MASK:
			irq_rtc &= ~irq_data->enable;
			break;
		case MAX8925_TSC_IRQ_MASK:
			irq_tsc &= ~irq_data->enable;
			break;
		default:
			dev_err(chip->dev, "wrong IRQ\n");
			break;
		}
	}
	/* update mask into registers */
	if (cache_chg[0] != irq_chg[0]) {
		cache_chg[0] = irq_chg[0];
		max8925_reg_write(chip->i2c, MAX8925_CHG_IRQ1_MASK,
			irq_chg[0]);
	}
	if (cache_chg[1] != irq_chg[1]) {
		cache_chg[1] = irq_chg[1];
		max8925_reg_write(chip->i2c, MAX8925_CHG_IRQ2_MASK,
			irq_chg[1]);
	}
	if (cache_on[0] != irq_on[0]) {
		cache_on[0] = irq_on[0];
		max8925_reg_write(chip->i2c, MAX8925_ON_OFF_IRQ1_MASK,
				irq_on[0]);
	}
	if (cache_on[1] != irq_on[1]) {
		cache_on[1] = irq_on[1];
		max8925_reg_write(chip->i2c, MAX8925_ON_OFF_IRQ2_MASK,
				irq_on[1]);
	}
	if (cache_rtc != irq_rtc) {
		cache_rtc = irq_rtc;
		max8925_reg_write(chip->rtc, MAX8925_RTC_IRQ_MASK, irq_rtc);
	}
	if (cache_tsc != irq_tsc) {
		cache_tsc = irq_tsc;
		max8925_reg_write(chip->adc, MAX8925_TSC_IRQ_MASK, irq_tsc);
	}

	mutex_unlock(&chip->irq_lock);
}