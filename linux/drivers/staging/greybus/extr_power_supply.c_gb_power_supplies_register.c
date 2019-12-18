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
struct gb_power_supplies {int supplies_count; int /*<<< orphan*/  supplies_lock; int /*<<< orphan*/ * supply; struct gb_connection* connection; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_power_supply_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_power_supplies_register(struct gb_power_supplies *supplies)
{
	struct gb_connection *connection = supplies->connection;
	int ret = 0;
	int i;

	mutex_lock(&supplies->supplies_lock);

	for (i = 0; i < supplies->supplies_count; i++) {
		ret = gb_power_supply_enable(&supplies->supply[i]);
		if (ret < 0) {
			dev_err(&connection->bundle->dev,
				"Fail to enable supplies devices\n");
			break;
		}
	}

	mutex_unlock(&supplies->supplies_lock);
	return ret;
}