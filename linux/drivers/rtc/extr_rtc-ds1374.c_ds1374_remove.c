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
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct ds1374 {int exiting; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,scalar_t__,struct i2c_client*) ; 
 TYPE_1__ ds1374_miscdev ; 
 int /*<<< orphan*/  ds1374_wdt_notifier ; 
 struct ds1374* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1374_remove(struct i2c_client *client)
{
	struct ds1374 *ds1374 = i2c_get_clientdata(client);
#ifdef CONFIG_RTC_DRV_DS1374_WDT
	misc_deregister(&ds1374_miscdev);
	ds1374_miscdev.parent = NULL;
	unregister_reboot_notifier(&ds1374_wdt_notifier);
#endif

	if (client->irq > 0) {
		mutex_lock(&ds1374->mutex);
		ds1374->exiting = 1;
		mutex_unlock(&ds1374->mutex);

		devm_free_irq(&client->dev, client->irq, client);
		cancel_work_sync(&ds1374->work);
	}

	return 0;
}