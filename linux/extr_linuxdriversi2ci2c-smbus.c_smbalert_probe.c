#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_smbus_alert_setup {int irq; } ;
struct i2c_smbus_alert {struct i2c_client* ara; int /*<<< orphan*/  alert; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct i2c_adapter {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 struct i2c_smbus_alert_setup* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct i2c_smbus_alert* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_smbus_alert*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct i2c_smbus_alert*) ; 
 int of_irq_get_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smbalert_work ; 
 int /*<<< orphan*/  smbus_alert ; 

__attribute__((used)) static int smbalert_probe(struct i2c_client *ara,
			  const struct i2c_device_id *id)
{
	struct i2c_smbus_alert_setup *setup = dev_get_platdata(&ara->dev);
	struct i2c_smbus_alert *alert;
	struct i2c_adapter *adapter = ara->adapter;
	int res, irq;

	alert = devm_kzalloc(&ara->dev, sizeof(struct i2c_smbus_alert),
			     GFP_KERNEL);
	if (!alert)
		return -ENOMEM;

	if (setup) {
		irq = setup->irq;
	} else {
		irq = of_irq_get_byname(adapter->dev.of_node, "smbus_alert");
		if (irq <= 0)
			return irq;
	}

	INIT_WORK(&alert->alert, smbalert_work);
	alert->ara = ara;

	if (irq > 0) {
		res = devm_request_threaded_irq(&ara->dev, irq,
						NULL, smbus_alert,
						IRQF_SHARED | IRQF_ONESHOT,
						"smbus_alert", alert);
		if (res)
			return res;
	}

	i2c_set_clientdata(ara, alert);
	dev_info(&adapter->dev, "supports SMBALERT#\n");

	return 0;
}