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
struct palmas_platform_data {int /*<<< orphan*/  irq_flags; } ;
struct irq_data {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_get_trigger_type (struct irq_data*) ; 

__attribute__((used)) static int palmas_set_pdata_irq_flag(struct i2c_client *i2c,
		struct palmas_platform_data *pdata)
{
	struct irq_data *irq_data = irq_get_irq_data(i2c->irq);
	if (!irq_data) {
		dev_err(&i2c->dev, "Invalid IRQ: %d\n", i2c->irq);
		return -EINVAL;
	}

	pdata->irq_flags = irqd_get_trigger_type(irq_data);
	dev_info(&i2c->dev, "Irq flag is 0x%08x\n", pdata->irq_flags);
	return 0;
}