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
struct w1_slave {int /*<<< orphan*/  dev; } ;
struct bq27xxx_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bq27xxx_battery_teardown (struct bq27xxx_device_info*) ; 
 struct bq27xxx_device_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bq27xxx_battery_hdq_remove_slave(struct w1_slave *sl)
{
	struct bq27xxx_device_info *di = dev_get_drvdata(&sl->dev);

	bq27xxx_battery_teardown(di);
}