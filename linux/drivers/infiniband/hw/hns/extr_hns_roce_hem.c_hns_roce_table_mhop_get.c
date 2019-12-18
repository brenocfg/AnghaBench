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
struct hns_roce_hem_table {size_t num_hem; size_t** bt_l0; size_t* bt_l0_dma_addr; size_t** bt_l1; size_t* bt_l1_dma_addr; int /*<<< orphan*/  mutex; TYPE_2__** hem; int /*<<< orphan*/  type; scalar_t__ lowmem; } ;
struct hns_roce_hem_mhop {int buf_chunk_size; int bt_chunk_size; int hop_num; int l0_idx; int l1_idx; int l2_idx; } ;
struct hns_roce_hem_iter {int dummy; } ;
struct hns_roce_dev {TYPE_1__* hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {scalar_t__ (* set_hem ) (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ;} ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_HIGHUSER ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  HEM_TYPE_MTT ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 int PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 scalar_t__ check_whether_bt_num_2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_whether_bt_num_3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dma_alloc_coherent (struct device*,int,size_t*,int) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,size_t*,size_t) ; 
 TYPE_2__* hns_roce_alloc_hem (struct hns_roce_dev*,int,int,int) ; 
 int hns_roce_calc_hem_mhop (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long*,struct hns_roce_hem_mhop*) ; 
 int hns_roce_get_bt_num (int /*<<< orphan*/ ,int) ; 
 size_t hns_roce_hem_addr (struct hns_roce_hem_iter*) ; 
 int /*<<< orphan*/  hns_roce_hem_first (TYPE_2__*,struct hns_roce_hem_iter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub2 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ stub3 (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns_roce_table_mhop_get(struct hns_roce_dev *hr_dev,
				   struct hns_roce_hem_table *table,
				   unsigned long obj)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_hem_mhop mhop;
	struct hns_roce_hem_iter iter;
	u32 buf_chunk_size;
	u32 bt_chunk_size;
	u32 chunk_ba_num;
	u32 hop_num;
	u32 size;
	u32 bt_num;
	u64 hem_idx;
	u64 bt_l1_idx = 0;
	u64 bt_l0_idx = 0;
	u64 bt_ba;
	unsigned long mhop_obj = obj;
	int bt_l1_allocated = 0;
	int bt_l0_allocated = 0;
	int step_idx;
	int ret;

	ret = hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, &mhop);
	if (ret)
		return ret;

	buf_chunk_size = mhop.buf_chunk_size;
	bt_chunk_size = mhop.bt_chunk_size;
	hop_num = mhop.hop_num;
	chunk_ba_num = bt_chunk_size / BA_BYTE_LEN;

	bt_num = hns_roce_get_bt_num(table->type, hop_num);
	switch (bt_num) {
	case 3:
		hem_idx = mhop.l0_idx * chunk_ba_num * chunk_ba_num +
			  mhop.l1_idx * chunk_ba_num + mhop.l2_idx;
		bt_l1_idx = mhop.l0_idx * chunk_ba_num + mhop.l1_idx;
		bt_l0_idx = mhop.l0_idx;
		break;
	case 2:
		hem_idx = mhop.l0_idx * chunk_ba_num + mhop.l1_idx;
		bt_l0_idx = mhop.l0_idx;
		break;
	case 1:
		hem_idx = mhop.l0_idx;
		break;
	default:
		dev_err(dev, "Table %d not support hop_num = %d!\n",
			     table->type, hop_num);
		return -EINVAL;
	}

	if (unlikely(hem_idx >= table->num_hem)) {
		dev_err(dev, "Table %d exceed hem limt idx = %llu,max = %lu!\n",
			     table->type, hem_idx, table->num_hem);
		return -EINVAL;
	}

	mutex_lock(&table->mutex);

	if (table->hem[hem_idx]) {
		++table->hem[hem_idx]->refcount;
		goto out;
	}

	/* alloc L1 BA's chunk */
	if ((check_whether_bt_num_3(table->type, hop_num) ||
		check_whether_bt_num_2(table->type, hop_num)) &&
		!table->bt_l0[bt_l0_idx]) {
		table->bt_l0[bt_l0_idx] = dma_alloc_coherent(dev, bt_chunk_size,
					    &(table->bt_l0_dma_addr[bt_l0_idx]),
					    GFP_KERNEL);
		if (!table->bt_l0[bt_l0_idx]) {
			ret = -ENOMEM;
			goto out;
		}
		bt_l0_allocated = 1;

		/* set base address to hardware */
		if (table->type < HEM_TYPE_MTT) {
			step_idx = 0;
			if (hr_dev->hw->set_hem(hr_dev, table, obj, step_idx)) {
				ret = -ENODEV;
				dev_err(dev, "set HEM base address to HW failed!\n");
				goto err_dma_alloc_l1;
			}
		}
	}

	/* alloc L2 BA's chunk */
	if (check_whether_bt_num_3(table->type, hop_num) &&
	    !table->bt_l1[bt_l1_idx])  {
		table->bt_l1[bt_l1_idx] = dma_alloc_coherent(dev, bt_chunk_size,
					    &(table->bt_l1_dma_addr[bt_l1_idx]),
					    GFP_KERNEL);
		if (!table->bt_l1[bt_l1_idx]) {
			ret = -ENOMEM;
			goto err_dma_alloc_l1;
		}
		bt_l1_allocated = 1;
		*(table->bt_l0[bt_l0_idx] + mhop.l1_idx) =
					       table->bt_l1_dma_addr[bt_l1_idx];

		/* set base address to hardware */
		step_idx = 1;
		if (hr_dev->hw->set_hem(hr_dev, table, obj, step_idx)) {
			ret = -ENODEV;
			dev_err(dev, "set HEM base address to HW failed!\n");
			goto err_alloc_hem_buf;
		}
	}

	/*
	 * alloc buffer space chunk for QPC/MTPT/CQC/SRQC/SCCC.
	 * alloc bt space chunk for MTT/CQE.
	 */
	size = table->type < HEM_TYPE_MTT ? buf_chunk_size : bt_chunk_size;
	table->hem[hem_idx] = hns_roce_alloc_hem(hr_dev,
						size >> PAGE_SHIFT,
						size,
						(table->lowmem ? GFP_KERNEL :
						GFP_HIGHUSER) | __GFP_NOWARN);
	if (!table->hem[hem_idx]) {
		ret = -ENOMEM;
		goto err_alloc_hem_buf;
	}

	hns_roce_hem_first(table->hem[hem_idx], &iter);
	bt_ba = hns_roce_hem_addr(&iter);

	if (table->type < HEM_TYPE_MTT) {
		if (hop_num == 2) {
			*(table->bt_l1[bt_l1_idx] + mhop.l2_idx) = bt_ba;
			step_idx = 2;
		} else if (hop_num == 1) {
			*(table->bt_l0[bt_l0_idx] + mhop.l1_idx) = bt_ba;
			step_idx = 1;
		} else if (hop_num == HNS_ROCE_HOP_NUM_0) {
			step_idx = 0;
		} else {
			ret = -EINVAL;
			goto err_dma_alloc_l1;
		}

		/* set HEM base address to hardware */
		if (hr_dev->hw->set_hem(hr_dev, table, obj, step_idx)) {
			ret = -ENODEV;
			dev_err(dev, "set HEM base address to HW failed!\n");
			goto err_alloc_hem_buf;
		}
	} else if (hop_num == 2) {
		*(table->bt_l0[bt_l0_idx] + mhop.l1_idx) = bt_ba;
	}

	++table->hem[hem_idx]->refcount;
	goto out;

err_alloc_hem_buf:
	if (bt_l1_allocated) {
		dma_free_coherent(dev, bt_chunk_size, table->bt_l1[bt_l1_idx],
				  table->bt_l1_dma_addr[bt_l1_idx]);
		table->bt_l1[bt_l1_idx] = NULL;
	}

err_dma_alloc_l1:
	if (bt_l0_allocated) {
		dma_free_coherent(dev, bt_chunk_size, table->bt_l0[bt_l0_idx],
				  table->bt_l0_dma_addr[bt_l0_idx]);
		table->bt_l0[bt_l0_idx] = NULL;
	}

out:
	mutex_unlock(&table->mutex);
	return ret;
}