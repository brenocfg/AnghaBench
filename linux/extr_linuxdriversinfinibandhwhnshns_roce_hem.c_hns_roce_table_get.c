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
struct hns_roce_hem_table {int num_obj; unsigned long table_chunk_size; unsigned long obj_size; int /*<<< orphan*/  mutex; TYPE_1__** hem; scalar_t__ lowmem; int /*<<< orphan*/  type; } ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_HIGHUSER ; 
 int GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_1__* hns_roce_alloc_hem (struct hns_roce_dev*,int,int,int) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_hem (struct hns_roce_dev*,TYPE_1__*) ; 
 scalar_t__ hns_roce_set_hem (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long) ; 
 int hns_roce_table_mhop_get (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hns_roce_table_get(struct hns_roce_dev *hr_dev,
		       struct hns_roce_hem_table *table, unsigned long obj)
{
	struct device *dev = hr_dev->dev;
	int ret = 0;
	unsigned long i;

	if (hns_roce_check_whether_mhop(hr_dev, table->type))
		return hns_roce_table_mhop_get(hr_dev, table, obj);

	i = (obj & (table->num_obj - 1)) / (table->table_chunk_size /
	     table->obj_size);

	mutex_lock(&table->mutex);

	if (table->hem[i]) {
		++table->hem[i]->refcount;
		goto out;
	}

	table->hem[i] = hns_roce_alloc_hem(hr_dev,
				       table->table_chunk_size >> PAGE_SHIFT,
				       table->table_chunk_size,
				       (table->lowmem ? GFP_KERNEL :
					GFP_HIGHUSER) | __GFP_NOWARN);
	if (!table->hem[i]) {
		ret = -ENOMEM;
		goto out;
	}

	/* Set HEM base address(128K/page, pa) to Hardware */
	if (hns_roce_set_hem(hr_dev, table, obj)) {
		hns_roce_free_hem(hr_dev, table->hem[i]);
		table->hem[i] = NULL;
		ret = -ENODEV;
		dev_err(dev, "set HEM base address to HW failed.\n");
		goto out;
	}

	++table->hem[i]->refcount;
out:
	mutex_unlock(&table->mutex);
	return ret;
}