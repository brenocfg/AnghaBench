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
struct power_supply {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {size_t vindpm; } ;
struct bq24257_device {TYPE_1__ init_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * bq24257_vindpm_map ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct bq24257_device* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bq24257_show_in_dpm_voltage(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq24257_device *bq = power_supply_get_drvdata(psy);

	return scnprintf(buf, PAGE_SIZE, "%u\n",
			 bq24257_vindpm_map[bq->init_data.vindpm]);
}