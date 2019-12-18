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
struct smb347_charger_platform_data {int /*<<< orphan*/  irq_gpio; } ;
struct smb347_charger {int /*<<< orphan*/  regmap; struct smb347_charger_platform_data* pdata; } ;
struct i2c_client {int irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STAT ; 
 int CFG_STAT_ACTIVE_HIGH ; 
 int CFG_STAT_DISABLED ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  free_irq (int,struct smb347_charger*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct smb347_charger*) ; 
 int /*<<< orphan*/  smb347_interrupt ; 
 int smb347_set_writable (struct smb347_charger*,int) ; 

__attribute__((used)) static int smb347_irq_init(struct smb347_charger *smb,
			   struct i2c_client *client)
{
	const struct smb347_charger_platform_data *pdata = smb->pdata;
	int ret, irq = gpio_to_irq(pdata->irq_gpio);

	ret = gpio_request_one(pdata->irq_gpio, GPIOF_IN, client->name);
	if (ret < 0)
		goto fail;

	ret = request_threaded_irq(irq, NULL, smb347_interrupt,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   client->name, smb);
	if (ret < 0)
		goto fail_gpio;

	ret = smb347_set_writable(smb, true);
	if (ret < 0)
		goto fail_irq;

	/*
	 * Configure the STAT output to be suitable for interrupts: disable
	 * all other output (except interrupts) and make it active low.
	 */
	ret = regmap_update_bits(smb->regmap, CFG_STAT,
				 CFG_STAT_ACTIVE_HIGH | CFG_STAT_DISABLED,
				 CFG_STAT_DISABLED);
	if (ret < 0)
		goto fail_readonly;

	smb347_set_writable(smb, false);
	client->irq = irq;
	return 0;

fail_readonly:
	smb347_set_writable(smb, false);
fail_irq:
	free_irq(irq, smb);
fail_gpio:
	gpio_free(pdata->irq_gpio);
fail:
	client->irq = 0;
	return ret;
}