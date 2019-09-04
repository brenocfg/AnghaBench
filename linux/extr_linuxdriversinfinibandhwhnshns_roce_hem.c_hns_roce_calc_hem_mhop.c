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
typedef  unsigned long u32 ;
struct hns_roce_hem_table {int type; int num_obj; unsigned long obj_size; } ;
struct hns_roce_hem_mhop {int buf_chunk_size; int bt_chunk_size; int ba_l0_num; unsigned long l2_idx; unsigned long l1_idx; unsigned long l0_idx; int /*<<< orphan*/  hop_num; } ;
struct TYPE_2__ {int qpc_buf_pg_sz; int qpc_ba_pg_sz; int qpc_bt_num; int mpt_buf_pg_sz; int mpt_ba_pg_sz; int mpt_bt_num; int cqc_buf_pg_sz; int cqc_ba_pg_sz; int cqc_bt_num; int srqc_buf_pg_sz; int srqc_ba_pg_sz; int srqc_bt_num; int mtt_buf_pg_sz; int mtt_ba_pg_sz; int cqe_buf_pg_sz; int cqe_ba_pg_sz; int /*<<< orphan*/  cqe_hop_num; int /*<<< orphan*/  mtt_hop_num; int /*<<< orphan*/  srqc_hop_num; int /*<<< orphan*/  cqc_hop_num; int /*<<< orphan*/  mpt_hop_num; int /*<<< orphan*/  qpc_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HEM_TYPE_CQC 133 
#define  HEM_TYPE_CQE 132 
#define  HEM_TYPE_MTPT 131 
#define  HEM_TYPE_MTT 130 
#define  HEM_TYPE_QPC 129 
#define  HEM_TYPE_SRQC 128 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int const,...) ; 
 unsigned long hns_roce_get_bt_num (int,int /*<<< orphan*/ ) ; 

int hns_roce_calc_hem_mhop(struct hns_roce_dev *hr_dev,
			   struct hns_roce_hem_table *table, unsigned long *obj,
			   struct hns_roce_hem_mhop *mhop)
{
	struct device *dev = hr_dev->dev;
	u32 chunk_ba_num;
	u32 table_idx;
	u32 bt_num;
	u32 chunk_size;

	switch (table->type) {
	case HEM_TYPE_QPC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.qpc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.qpc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.qpc_bt_num;
		mhop->hop_num = hr_dev->caps.qpc_hop_num;
		break;
	case HEM_TYPE_MTPT:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.mpt_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.mpt_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.mpt_bt_num;
		mhop->hop_num = hr_dev->caps.mpt_hop_num;
		break;
	case HEM_TYPE_CQC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.cqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.cqc_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.cqc_bt_num;
		mhop->hop_num = hr_dev->caps.cqc_hop_num;
		break;
	case HEM_TYPE_SRQC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.srqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.srqc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.srqc_bt_num;
		mhop->hop_num = hr_dev->caps.srqc_hop_num;
		break;
	case HEM_TYPE_MTT:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.mtt_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.mtt_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = mhop->bt_chunk_size / 8;
		mhop->hop_num = hr_dev->caps.mtt_hop_num;
		break;
	case HEM_TYPE_CQE:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.cqe_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.cqe_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = mhop->bt_chunk_size / 8;
		mhop->hop_num = hr_dev->caps.cqe_hop_num;
		break;
	default:
		dev_err(dev, "Table %d not support multi-hop addressing!\n",
			 table->type);
		return -EINVAL;
	}

	if (!obj)
		return 0;

	/*
	 * QPC/MTPT/CQC/SRQC alloc hem for buffer pages.
	 * MTT/CQE alloc hem for bt pages.
	 */
	bt_num = hns_roce_get_bt_num(table->type, mhop->hop_num);
	chunk_ba_num = mhop->bt_chunk_size / 8;
	chunk_size = table->type < HEM_TYPE_MTT ? mhop->buf_chunk_size :
			      mhop->bt_chunk_size;
	table_idx = (*obj & (table->num_obj - 1)) /
		     (chunk_size / table->obj_size);
	switch (bt_num) {
	case 3:
		mhop->l2_idx = table_idx & (chunk_ba_num - 1);
		mhop->l1_idx = table_idx / chunk_ba_num & (chunk_ba_num - 1);
		mhop->l0_idx = (table_idx / chunk_ba_num) / chunk_ba_num;
		break;
	case 2:
		mhop->l1_idx = table_idx & (chunk_ba_num - 1);
		mhop->l0_idx = table_idx / chunk_ba_num;
		break;
	case 1:
		mhop->l0_idx = table_idx;
		break;
	default:
		dev_err(dev, "Table %d not support hop_num = %d!\n",
			     table->type, mhop->hop_num);
		return -EINVAL;
	}
	if (mhop->l0_idx >= mhop->ba_l0_num)
		mhop->l0_idx %= mhop->ba_l0_num;

	return 0;
}