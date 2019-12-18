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
struct hns_roce_hem_table {int num_obj; unsigned long table_chunk_size; unsigned long obj_size; int /*<<< orphan*/  mutex; TYPE_2__** hem; int /*<<< orphan*/  type; } ;
struct hns_roce_dev {TYPE_1__* hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ refcount; } ;
struct TYPE_3__ {scalar_t__ (* clear_hem ) (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_hem (struct hns_roce_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  hns_roce_table_mhop_put (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int /*<<< orphan*/ ) ; 

void hns_roce_table_put(struct hns_roce_dev *hr_dev,
			struct hns_roce_hem_table *table, unsigned long obj)
{
	struct device *dev = hr_dev->dev;
	unsigned long i;

	if (hns_roce_check_whether_mhop(hr_dev, table->type)) {
		hns_roce_table_mhop_put(hr_dev, table, obj, 1);
		return;
	}

	i = (obj & (table->num_obj - 1)) /
	    (table->table_chunk_size / table->obj_size);

	mutex_lock(&table->mutex);

	if (--table->hem[i]->refcount == 0) {
		/* Clear HEM base address */
		if (hr_dev->hw->clear_hem(hr_dev, table, obj, 0))
			dev_warn(dev, "Clear HEM base address failed.\n");

		hns_roce_free_hem(hr_dev, table->hem[i]);
		table->hem[i] = NULL;
	}

	mutex_unlock(&table->mutex);
}