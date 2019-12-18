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
typedef  int u64 ;
typedef  int u32 ;
struct hns_roce_hem_table {scalar_t__ type; int num_hem; int obj_size; scalar_t__* bt_l0_dma_addr; scalar_t__* bt_l0; scalar_t__* bt_l1_dma_addr; scalar_t__* bt_l1; scalar_t__* hem; } ;
struct hns_roce_hem_mhop {int buf_chunk_size; int bt_chunk_size; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HEM_TYPE_MTT ; 
 scalar_t__ hns_roce_calc_hem_mhop (struct hns_roce_dev*,struct hns_roce_hem_table*,int /*<<< orphan*/ *,struct hns_roce_hem_mhop*) ; 
 int /*<<< orphan*/  hns_roce_table_mhop_put (struct hns_roce_dev*,struct hns_roce_hem_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 

__attribute__((used)) static void hns_roce_cleanup_mhop_hem_table(struct hns_roce_dev *hr_dev,
					    struct hns_roce_hem_table *table)
{
	struct hns_roce_hem_mhop mhop;
	u32 buf_chunk_size;
	int i;
	u64 obj;

	if (hns_roce_calc_hem_mhop(hr_dev, table, NULL, &mhop))
		return;
	buf_chunk_size = table->type < HEM_TYPE_MTT ? mhop.buf_chunk_size :
					mhop.bt_chunk_size;

	for (i = 0; i < table->num_hem; ++i) {
		obj = i * buf_chunk_size / table->obj_size;
		if (table->hem[i])
			hns_roce_table_mhop_put(hr_dev, table, obj, 0);
	}

	kfree(table->hem);
	table->hem = NULL;
	kfree(table->bt_l1);
	table->bt_l1 = NULL;
	kfree(table->bt_l1_dma_addr);
	table->bt_l1_dma_addr = NULL;
	kfree(table->bt_l0);
	table->bt_l0 = NULL;
	kfree(table->bt_l0_dma_addr);
	table->bt_l0_dma_addr = NULL;
}