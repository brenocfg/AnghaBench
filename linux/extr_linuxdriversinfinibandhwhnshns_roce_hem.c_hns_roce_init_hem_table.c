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
typedef  int u32 ;
struct hns_roce_hem_table {unsigned long table_chunk_size; int type; unsigned long num_hem; unsigned long num_obj; unsigned long obj_size; int lowmem; int /*<<< orphan*/ * hem; int /*<<< orphan*/ * bt_l1; int /*<<< orphan*/ * bt_l1_dma_addr; int /*<<< orphan*/ * bt_l0; int /*<<< orphan*/  mutex; void* bt_l0_dma_addr; } ;
struct TYPE_2__ {unsigned long chunk_sz; int qpc_buf_pg_sz; int qpc_ba_pg_sz; unsigned long qpc_bt_num; int qpc_hop_num; int mpt_buf_pg_sz; int mpt_ba_pg_sz; unsigned long mpt_bt_num; int mpt_hop_num; int cqc_buf_pg_sz; int cqc_ba_pg_sz; unsigned long cqc_bt_num; int cqc_hop_num; int srqc_buf_pg_sz; int srqc_ba_pg_sz; unsigned long srqc_bt_num; int srqc_hop_num; int mtt_ba_pg_sz; int mtt_hop_num; int cqe_ba_pg_sz; int cqe_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HEM_TYPE_CQC 133 
#define  HEM_TYPE_CQE 132 
#define  HEM_TYPE_MTPT 131 
#define  HEM_TYPE_MTT 130 
#define  HEM_TYPE_QPC 129 
#define  HEM_TYPE_SRQC 128 
 int PAGE_SHIFT ; 
 scalar_t__ check_whether_bt_num_2 (int,int) ; 
 scalar_t__ check_whether_bt_num_3 (int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  hns_roce_check_whether_mhop (struct hns_roce_dev*,int) ; 
 void* kcalloc (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int hns_roce_init_hem_table(struct hns_roce_dev *hr_dev,
			    struct hns_roce_hem_table *table, u32 type,
			    unsigned long obj_size, unsigned long nobj,
			    int use_lowmem)
{
	struct device *dev = hr_dev->dev;
	unsigned long obj_per_chunk;
	unsigned long num_hem;

	if (!hns_roce_check_whether_mhop(hr_dev, type)) {
		table->table_chunk_size = hr_dev->caps.chunk_sz;
		obj_per_chunk = table->table_chunk_size / obj_size;
		num_hem = (nobj + obj_per_chunk - 1) / obj_per_chunk;

		table->hem = kcalloc(num_hem, sizeof(*table->hem), GFP_KERNEL);
		if (!table->hem)
			return -ENOMEM;
	} else {
		unsigned long buf_chunk_size;
		unsigned long bt_chunk_size;
		unsigned long bt_chunk_num;
		unsigned long num_bt_l0 = 0;
		u32 hop_num;

		switch (type) {
		case HEM_TYPE_QPC:
			buf_chunk_size = 1 << (hr_dev->caps.qpc_buf_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = 1 << (hr_dev->caps.qpc_ba_pg_sz
					+ PAGE_SHIFT);
			num_bt_l0 = hr_dev->caps.qpc_bt_num;
			hop_num = hr_dev->caps.qpc_hop_num;
			break;
		case HEM_TYPE_MTPT:
			buf_chunk_size = 1 << (hr_dev->caps.mpt_buf_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = 1 << (hr_dev->caps.mpt_ba_pg_sz
					+ PAGE_SHIFT);
			num_bt_l0 = hr_dev->caps.mpt_bt_num;
			hop_num = hr_dev->caps.mpt_hop_num;
			break;
		case HEM_TYPE_CQC:
			buf_chunk_size = 1 << (hr_dev->caps.cqc_buf_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = 1 << (hr_dev->caps.cqc_ba_pg_sz
					+ PAGE_SHIFT);
			num_bt_l0 = hr_dev->caps.cqc_bt_num;
			hop_num = hr_dev->caps.cqc_hop_num;
			break;
		case HEM_TYPE_SRQC:
			buf_chunk_size = 1 << (hr_dev->caps.srqc_buf_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = 1 << (hr_dev->caps.srqc_ba_pg_sz
					+ PAGE_SHIFT);
			num_bt_l0 = hr_dev->caps.srqc_bt_num;
			hop_num = hr_dev->caps.srqc_hop_num;
			break;
		case HEM_TYPE_MTT:
			buf_chunk_size = 1 << (hr_dev->caps.mtt_ba_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = buf_chunk_size;
			hop_num = hr_dev->caps.mtt_hop_num;
			break;
		case HEM_TYPE_CQE:
			buf_chunk_size = 1 << (hr_dev->caps.cqe_ba_pg_sz
					+ PAGE_SHIFT);
			bt_chunk_size = buf_chunk_size;
			hop_num = hr_dev->caps.cqe_hop_num;
			break;
		default:
			dev_err(dev,
			  "Table %d not support to init hem table here!\n",
			  type);
			return -EINVAL;
		}
		obj_per_chunk = buf_chunk_size / obj_size;
		num_hem = (nobj + obj_per_chunk - 1) / obj_per_chunk;
		bt_chunk_num = bt_chunk_size / 8;
		if (type >= HEM_TYPE_MTT)
			num_bt_l0 = bt_chunk_num;

		table->hem = kcalloc(num_hem, sizeof(*table->hem),
					 GFP_KERNEL);
		if (!table->hem)
			goto err_kcalloc_hem_buf;

		if (check_whether_bt_num_3(type, hop_num)) {
			unsigned long num_bt_l1;

			num_bt_l1 = (num_hem + bt_chunk_num - 1) /
					     bt_chunk_num;
			table->bt_l1 = kcalloc(num_bt_l1,
					       sizeof(*table->bt_l1),
					       GFP_KERNEL);
			if (!table->bt_l1)
				goto err_kcalloc_bt_l1;

			table->bt_l1_dma_addr = kcalloc(num_bt_l1,
						 sizeof(*table->bt_l1_dma_addr),
						 GFP_KERNEL);

			if (!table->bt_l1_dma_addr)
				goto err_kcalloc_l1_dma;
		}

		if (check_whether_bt_num_2(type, hop_num) ||
			check_whether_bt_num_3(type, hop_num)) {
			table->bt_l0 = kcalloc(num_bt_l0, sizeof(*table->bt_l0),
					       GFP_KERNEL);
			if (!table->bt_l0)
				goto err_kcalloc_bt_l0;

			table->bt_l0_dma_addr = kcalloc(num_bt_l0,
						 sizeof(*table->bt_l0_dma_addr),
						 GFP_KERNEL);
			if (!table->bt_l0_dma_addr)
				goto err_kcalloc_l0_dma;
		}
	}

	table->type = type;
	table->num_hem = num_hem;
	table->num_obj = nobj;
	table->obj_size = obj_size;
	table->lowmem = use_lowmem;
	mutex_init(&table->mutex);

	return 0;

err_kcalloc_l0_dma:
	kfree(table->bt_l0);
	table->bt_l0 = NULL;

err_kcalloc_bt_l0:
	kfree(table->bt_l1_dma_addr);
	table->bt_l1_dma_addr = NULL;

err_kcalloc_l1_dma:
	kfree(table->bt_l1);
	table->bt_l1 = NULL;

err_kcalloc_bt_l1:
	kfree(table->hem);
	table->hem = NULL;

err_kcalloc_hem_buf:
	return -ENOMEM;
}