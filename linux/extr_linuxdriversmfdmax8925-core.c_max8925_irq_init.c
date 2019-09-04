#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max8925_platform_data {int tsc_irq; } ;
struct max8925_chip {scalar_t__ irq_base; int core_irq; int tsc_irq; TYPE_1__* dev; int /*<<< orphan*/  adc; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  rtc; int /*<<< orphan*/  i2c; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  MAX8925_ALARM0_CNTL ; 
 int /*<<< orphan*/  MAX8925_ALARM1_CNTL ; 
 int /*<<< orphan*/  MAX8925_CHG_IRQ1 ; 
 int /*<<< orphan*/  MAX8925_CHG_IRQ1_MASK ; 
 int /*<<< orphan*/  MAX8925_CHG_IRQ2 ; 
 int /*<<< orphan*/  MAX8925_CHG_IRQ2_MASK ; 
 int /*<<< orphan*/  MAX8925_NR_IRQS ; 
 int /*<<< orphan*/  MAX8925_ON_OFF_IRQ1 ; 
 int /*<<< orphan*/  MAX8925_ON_OFF_IRQ1_MASK ; 
 int /*<<< orphan*/  MAX8925_ON_OFF_IRQ2 ; 
 int /*<<< orphan*/  MAX8925_ON_OFF_IRQ2_MASK ; 
 int /*<<< orphan*/  MAX8925_RTC_IRQ ; 
 int /*<<< orphan*/  MAX8925_RTC_IRQ_MASK ; 
 int /*<<< orphan*/  MAX8925_TSC_IRQ ; 
 int /*<<< orphan*/  MAX8925_TSC_IRQ_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 scalar_t__ irq_alloc_descs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_legacy (struct device_node*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct max8925_chip*) ; 
 int /*<<< orphan*/  max8925_irq ; 
 int /*<<< orphan*/  max8925_irq_domain_ops ; 
 int /*<<< orphan*/  max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max8925_tsc_irq ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,char*,struct max8925_chip*) ; 

__attribute__((used)) static int max8925_irq_init(struct max8925_chip *chip, int irq,
			    struct max8925_platform_data *pdata)
{
	unsigned long flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
	int ret;
	struct device_node *node = chip->dev->of_node;

	/* clear all interrupts */
	max8925_reg_read(chip->i2c, MAX8925_CHG_IRQ1);
	max8925_reg_read(chip->i2c, MAX8925_CHG_IRQ2);
	max8925_reg_read(chip->i2c, MAX8925_ON_OFF_IRQ1);
	max8925_reg_read(chip->i2c, MAX8925_ON_OFF_IRQ2);
	max8925_reg_read(chip->rtc, MAX8925_RTC_IRQ);
	max8925_reg_read(chip->adc, MAX8925_TSC_IRQ);
	/* mask all interrupts except for TSC */
	max8925_reg_write(chip->rtc, MAX8925_ALARM0_CNTL, 0);
	max8925_reg_write(chip->rtc, MAX8925_ALARM1_CNTL, 0);
	max8925_reg_write(chip->i2c, MAX8925_CHG_IRQ1_MASK, 0xff);
	max8925_reg_write(chip->i2c, MAX8925_CHG_IRQ2_MASK, 0xff);
	max8925_reg_write(chip->i2c, MAX8925_ON_OFF_IRQ1_MASK, 0xff);
	max8925_reg_write(chip->i2c, MAX8925_ON_OFF_IRQ2_MASK, 0xff);
	max8925_reg_write(chip->rtc, MAX8925_RTC_IRQ_MASK, 0xff);

	mutex_init(&chip->irq_lock);
	chip->irq_base = irq_alloc_descs(-1, 0, MAX8925_NR_IRQS, 0);
	if (chip->irq_base < 0) {
		dev_err(chip->dev, "Failed to allocate interrupts, ret:%d\n",
			chip->irq_base);
		return -EBUSY;
	}

	irq_domain_add_legacy(node, MAX8925_NR_IRQS, chip->irq_base, 0,
			      &max8925_irq_domain_ops, chip);

	/* request irq handler for pmic main irq*/
	chip->core_irq = irq;
	if (!chip->core_irq)
		return -EBUSY;
	ret = request_threaded_irq(irq, NULL, max8925_irq, flags | IRQF_ONESHOT,
				   "max8925", chip);
	if (ret) {
		dev_err(chip->dev, "Failed to request core IRQ: %d\n", ret);
		chip->core_irq = 0;
		return -EBUSY;
	}

	/* request irq handler for pmic tsc irq*/

	/* mask TSC interrupt */
	max8925_reg_write(chip->adc, MAX8925_TSC_IRQ_MASK, 0x0f);

	if (!pdata->tsc_irq) {
		dev_warn(chip->dev, "No interrupt support on TSC IRQ\n");
		return 0;
	}
	chip->tsc_irq = pdata->tsc_irq;
	ret = request_threaded_irq(chip->tsc_irq, NULL, max8925_tsc_irq,
				   flags | IRQF_ONESHOT, "max8925-tsc", chip);
	if (ret) {
		dev_err(chip->dev, "Failed to request TSC IRQ: %d\n", ret);
		chip->tsc_irq = 0;
	}
	return 0;
}