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
struct ksz_device {int /*<<< orphan*/  ds; int /*<<< orphan*/  vlan_mutex; int /*<<< orphan*/  alu_mutex; int /*<<< orphan*/  stats_mutex; int /*<<< orphan*/  reg_mutex; TYPE_1__* pdata; int /*<<< orphan*/  chip_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int dsa_register_switch (int /*<<< orphan*/ ) ; 
 scalar_t__ ksz_switch_detect (struct ksz_device*) ; 
 int ksz_switch_init (struct ksz_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ksz_switch_register(struct ksz_device *dev)
{
	int ret;

	if (dev->pdata)
		dev->chip_id = dev->pdata->chip_id;

	mutex_init(&dev->reg_mutex);
	mutex_init(&dev->stats_mutex);
	mutex_init(&dev->alu_mutex);
	mutex_init(&dev->vlan_mutex);

	if (ksz_switch_detect(dev))
		return -EINVAL;

	ret = ksz_switch_init(dev);
	if (ret)
		return ret;

	return dsa_register_switch(dev->ds);
}