#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  spec_minor; int /*<<< orphan*/  spec_major; int /*<<< orphan*/  version; } ;
struct kempld_device_data {TYPE_2__* dev; TYPE_1__ info; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_index; int /*<<< orphan*/  io_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int KEMPLD_MUTEX_KEY ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int kempld_get_info (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_get_type_string (struct kempld_device_data*) ; 
 int kempld_register_cells (struct kempld_device_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pld_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kempld_detect_device(struct kempld_device_data *pld)
{
	u8 index_reg;
	int ret;

	mutex_lock(&pld->lock);

	/* Check for empty IO space */
	index_reg = ioread8(pld->io_index);
	if (index_reg == 0xff && ioread8(pld->io_data) == 0xff) {
		mutex_unlock(&pld->lock);
		return -ENODEV;
	}

	/* Release hardware mutex if acquired */
	if (!(index_reg & KEMPLD_MUTEX_KEY)) {
		iowrite8(KEMPLD_MUTEX_KEY, pld->io_index);
		/* PXT and COMe-cPC2 boards may require a second release */
		iowrite8(KEMPLD_MUTEX_KEY, pld->io_index);
	}

	mutex_unlock(&pld->lock);

	ret = kempld_get_info(pld);
	if (ret)
		return ret;

	dev_info(pld->dev, "Found Kontron PLD - %s (%s), spec %d.%d\n",
		 pld->info.version, kempld_get_type_string(pld),
		 pld->info.spec_major, pld->info.spec_minor);

	ret = sysfs_create_group(&pld->dev->kobj, &pld_attr_group);
	if (ret)
		return ret;

	ret = kempld_register_cells(pld);
	if (ret)
		sysfs_remove_group(&pld->dev->kobj, &pld_attr_group);

	return ret;
}