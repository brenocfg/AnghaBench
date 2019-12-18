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
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct ds1374 {int /*<<< orphan*/  rtc; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 struct ds1374* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i2c_client*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ds1374_check_rtc_status (struct i2c_client*) ; 
 int /*<<< orphan*/  ds1374_irq ; 
 int /*<<< orphan*/  ds1374_miscdev ; 
 int /*<<< orphan*/  ds1374_rtc_ops ; 
 int /*<<< orphan*/  ds1374_wdt_notifier ; 
 int /*<<< orphan*/  ds1374_wdt_settimeout (int) ; 
 int /*<<< orphan*/  ds1374_work ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ds1374*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 struct i2c_client* save_client ; 

__attribute__((used)) static int ds1374_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ds1374 *ds1374;
	int ret;

	ds1374 = devm_kzalloc(&client->dev, sizeof(struct ds1374), GFP_KERNEL);
	if (!ds1374)
		return -ENOMEM;

	ds1374->client = client;
	i2c_set_clientdata(client, ds1374);

	INIT_WORK(&ds1374->work, ds1374_work);
	mutex_init(&ds1374->mutex);

	ret = ds1374_check_rtc_status(client);
	if (ret)
		return ret;

	if (client->irq > 0) {
		ret = devm_request_irq(&client->dev, client->irq, ds1374_irq, 0,
					"ds1374", client);
		if (ret) {
			dev_err(&client->dev, "unable to request IRQ\n");
			return ret;
		}

		device_set_wakeup_capable(&client->dev, 1);
	}

	ds1374->rtc = devm_rtc_device_register(&client->dev, client->name,
						&ds1374_rtc_ops, THIS_MODULE);
	if (IS_ERR(ds1374->rtc)) {
		dev_err(&client->dev, "unable to register the class device\n");
		return PTR_ERR(ds1374->rtc);
	}

#ifdef CONFIG_RTC_DRV_DS1374_WDT
	save_client = client;
	ret = misc_register(&ds1374_miscdev);
	if (ret)
		return ret;
	ret = register_reboot_notifier(&ds1374_wdt_notifier);
	if (ret) {
		misc_deregister(&ds1374_miscdev);
		return ret;
	}
	ds1374_wdt_settimeout(131072);
#endif

	return 0;
}