#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ddb {int i2c_num; int /*<<< orphan*/  ddb_dev; TYPE_2__* link; } ;
struct TYPE_14__ {scalar_t__ name; } ;
struct TYPE_15__ {TYPE_3__ attr; } ;
struct TYPE_13__ {TYPE_1__* info; } ;
struct TYPE_12__ {int temp_num; int fan_num; scalar_t__ led_num; scalar_t__ tempmon_irq; } ;

/* Variables and functions */
 TYPE_4__* ddb_attrs ; 
 TYPE_4__* ddb_attrs_ctemp ; 
 TYPE_4__* ddb_attrs_fan ; 
 TYPE_4__* ddb_attrs_fanspeed ; 
 TYPE_4__* ddb_attrs_led ; 
 TYPE_4__* ddb_attrs_snr ; 
 TYPE_4__* ddb_attrs_temp ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void ddb_device_attrs_del(struct ddb *dev)
{
	int i;

	for (i = 0; i < 4; i++)
		if (dev->link[i].info && dev->link[i].info->tempmon_irq)
			device_remove_file(dev->ddb_dev,
					   &ddb_attrs_fanspeed[i]);
	for (i = 0; i < dev->link[0].info->temp_num; i++)
		device_remove_file(dev->ddb_dev, &ddb_attrs_temp[i]);
	for (i = 0; i < dev->link[0].info->fan_num; i++)
		device_remove_file(dev->ddb_dev, &ddb_attrs_fan[i]);
	for (i = 0; i < dev->i2c_num && i < 4; i++) {
		if (dev->link[0].info->led_num)
			device_remove_file(dev->ddb_dev, &ddb_attrs_led[i]);
		device_remove_file(dev->ddb_dev, &ddb_attrs_snr[i]);
		device_remove_file(dev->ddb_dev, &ddb_attrs_ctemp[i]);
	}
	for (i = 0; ddb_attrs[i].attr.name; i++)
		device_remove_file(dev->ddb_dev, &ddb_attrs[i]);
}