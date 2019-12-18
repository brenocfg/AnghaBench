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
struct hns_roce_hem_table {unsigned long num_hem; unsigned long table_chunk_size; unsigned long obj_size; scalar_t__* hem; int /*<<< orphan*/  type; } ;
struct hns_roce_dev {TYPE_1__* hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* clear_hem ) (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cleanup_mhop_hem_table (struct hns_roce_dev*,struct hns_roce_hem_table*) ; 
 int /*<<< orphan*/  hns_roce_free_hem (struct hns_roce_dev*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__ stub1 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int /*<<< orphan*/ ) ; 

void hns_roce_cleanup_hem_table(struct hns_roce_dev *hr_dev,
				struct hns_roce_hem_table *table)
{
	struct device *dev = hr_dev->dev;
	unsigned long i;

	if (hns_roce_check_whether_mhop(hr_dev, table->type)) {
		hns_roce_cleanup_mhop_hem_table(hr_dev, table);
		return;
	}

	for (i = 0; i < table->num_hem; ++i)
		if (table->hem[i]) {
			if (hr_dev->hw->clear_hem(hr_dev, table,
			    i * table->table_chunk_size / table->obj_size, 0))
				dev_err(dev, "Clear HEM base address failed.\n");

			hns_roce_free_hem(hr_dev, table->hem[i]);
		}

	kfree(table->hem);
}