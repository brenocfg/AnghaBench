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
struct gb_power_supply {int registered; int /*<<< orphan*/  work; int /*<<< orphan*/  update_interval; int /*<<< orphan*/  supply_lock; int /*<<< orphan*/  name; int /*<<< orphan*/  model_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __gb_power_supply_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gb_power_supply_register (struct gb_power_supply*) ; 
 int /*<<< orphan*/  gb_power_supply_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_interval_init ; 

__attribute__((used)) static int gb_power_supply_enable(struct gb_power_supply *gbpsy)
{
	int ret;

	/* guarantee that we have an unique name, before register */
	ret =  __gb_power_supply_set_name(gbpsy->model_name, gbpsy->name,
					  sizeof(gbpsy->name));
	if (ret < 0)
		return ret;

	mutex_init(&gbpsy->supply_lock);

	ret = gb_power_supply_register(gbpsy);
	if (ret < 0)
		return ret;

	gbpsy->update_interval = update_interval_init;
	INIT_DELAYED_WORK(&gbpsy->work, gb_power_supply_work);
	schedule_delayed_work(&gbpsy->work, 0);

	/* everything went fine, mark it for release code to know */
	gbpsy->registered = true;

	return 0;
}