#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
typedef  int u32 ;
struct hns_roce_hem_table {scalar_t__ type; int /*<<< orphan*/  mutex; int /*<<< orphan*/ ** bt_l0; int /*<<< orphan*/ * bt_l0_dma_addr; int /*<<< orphan*/ ** bt_l1; int /*<<< orphan*/ * bt_l1_dma_addr; int /*<<< orphan*/  num_hem; TYPE_2__** hem; } ;
struct hns_roce_hem_mhop {int bt_chunk_size; int hop_num; int l0_idx; int l1_idx; int /*<<< orphan*/  l2_idx; } ;
struct hns_roce_dev {TYPE_1__* hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {scalar_t__ refcount; } ;
struct TYPE_4__ {scalar_t__ (* clear_hem ) (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ;} ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 scalar_t__ HEM_TYPE_MTT ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 scalar_t__ check_whether_bt_num_2 (scalar_t__,int) ; 
 scalar_t__ check_whether_bt_num_3 (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hns_roce_calc_hem_mhop (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long*,struct hns_roce_hem_mhop*) ; 
 scalar_t__ hns_roce_check_bt_null (int /*<<< orphan*/ **,int,int) ; 
 scalar_t__ hns_roce_check_hem_null (TYPE_2__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_hem (struct hns_roce_dev*,TYPE_2__*) ; 
 int hns_roce_get_bt_num (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub2 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub3 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub4 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub5 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub6 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 

__attribute__((used)) static void hns_roce_table_mhop_put(struct hns_roce_dev *hr_dev,
				    struct hns_roce_hem_table *table,
				    unsigned long obj,
				    int check_refcount)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_hem_mhop mhop;
	unsigned long mhop_obj = obj;
	u32 bt_chunk_size;
	u32 chunk_ba_num;
	u32 hop_num;
	u32 start_idx;
	u32 bt_num;
	u64 hem_idx;
	u64 bt_l1_idx = 0;
	int ret;

	ret = hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, &mhop);
	if (ret)
		return;

	bt_chunk_size = mhop.bt_chunk_size;
	hop_num = mhop.hop_num;
	chunk_ba_num = bt_chunk_size / BA_BYTE_LEN;

	bt_num = hns_roce_get_bt_num(table->type, hop_num);
	switch (bt_num) {
	case 3:
		hem_idx = mhop.l0_idx * chunk_ba_num * chunk_ba_num +
			  mhop.l1_idx * chunk_ba_num + mhop.l2_idx;
		bt_l1_idx = mhop.l0_idx * chunk_ba_num + mhop.l1_idx;
		break;
	case 2:
		hem_idx = mhop.l0_idx * chunk_ba_num + mhop.l1_idx;
		break;
	case 1:
		hem_idx = mhop.l0_idx;
		break;
	default:
		dev_err(dev, "Table %d not support hop_num = %d!\n",
			     table->type, hop_num);
		return;
	}

	mutex_lock(&table->mutex);

	if (check_refcount && (--table->hem[hem_idx]->refcount > 0)) {
		mutex_unlock(&table->mutex);
		return;
	}

	if (table->type < HEM_TYPE_MTT && hop_num == 1) {
		if (hr_dev->hw->clear_hem(hr_dev, table, obj, 1))
			dev_warn(dev, "Clear HEM base address failed.\n");
	} else if (table->type < HEM_TYPE_MTT && hop_num == 2) {
		if (hr_dev->hw->clear_hem(hr_dev, table, obj, 2))
			dev_warn(dev, "Clear HEM base address failed.\n");
	} else if (table->type < HEM_TYPE_MTT &&
		   hop_num == HNS_ROCE_HOP_NUM_0) {
		if (hr_dev->hw->clear_hem(hr_dev, table, obj, 0))
			dev_warn(dev, "Clear HEM base address failed.\n");
	}

	/*
	 * free buffer space chunk for QPC/MTPT/CQC/SRQC/SCCC.
	 * free bt space chunk for MTT/CQE.
	 */
	hns_roce_free_hem(hr_dev, table->hem[hem_idx]);
	table->hem[hem_idx] = NULL;

	if (check_whether_bt_num_2(table->type, hop_num)) {
		start_idx = mhop.l0_idx * chunk_ba_num;
		if (hns_roce_check_hem_null(table->hem, start_idx,
					    chunk_ba_num, table->num_hem)) {
			if (table->type < HEM_TYPE_MTT &&
			    hr_dev->hw->clear_hem(hr_dev, table, obj, 0))
				dev_warn(dev, "Clear HEM base address failed.\n");

			dma_free_coherent(dev, bt_chunk_size,
					  table->bt_l0[mhop.l0_idx],
					  table->bt_l0_dma_addr[mhop.l0_idx]);
			table->bt_l0[mhop.l0_idx] = NULL;
		}
	} else if (check_whether_bt_num_3(table->type, hop_num)) {
		start_idx = mhop.l0_idx * chunk_ba_num * chunk_ba_num +
			    mhop.l1_idx * chunk_ba_num;
		if (hns_roce_check_hem_null(table->hem, start_idx,
					    chunk_ba_num, table->num_hem)) {
			if (hr_dev->hw->clear_hem(hr_dev, table, obj, 1))
				dev_warn(dev, "Clear HEM base address failed.\n");

			dma_free_coherent(dev, bt_chunk_size,
					  table->bt_l1[bt_l1_idx],
					  table->bt_l1_dma_addr[bt_l1_idx]);
			table->bt_l1[bt_l1_idx] = NULL;

			start_idx = mhop.l0_idx * chunk_ba_num;
			if (hns_roce_check_bt_null(table->bt_l1, start_idx,
						   chunk_ba_num)) {
				if (hr_dev->hw->clear_hem(hr_dev, table, obj,
							  0))
					dev_warn(dev, "Clear HEM base address failed.\n");

				dma_free_coherent(dev, bt_chunk_size,
					    table->bt_l0[mhop.l0_idx],
					    table->bt_l0_dma_addr[mhop.l0_idx]);
				table->bt_l0[mhop.l0_idx] = NULL;
			}
		}
	}

	mutex_unlock(&table->mutex);
}