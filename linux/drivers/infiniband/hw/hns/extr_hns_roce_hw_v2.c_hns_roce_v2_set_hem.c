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
typedef  size_t u64 ;
typedef  int u32 ;
struct hns_roce_hem_table {scalar_t__ type; size_t* bt_l0_dma_addr; size_t* bt_l1_dma_addr; struct hns_roce_hem** hem; } ;
struct hns_roce_hem_mhop {int l0_idx; int l1_idx; int l2_idx; int hop_num; int bt_chunk_size; } ;
struct hns_roce_hem_iter {int dummy; } ;
struct hns_roce_hem {int dummy; } ;
struct hns_roce_dev {int dummy; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HEM_TYPE_SCCC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 scalar_t__ check_whether_last_step (int,int) ; 
 int get_op_for_set_hem (struct hns_roce_dev*,scalar_t__,int) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_calc_hem_mhop (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long*,struct hns_roce_hem_mhop*) ; 
 int /*<<< orphan*/  hns_roce_check_whether_mhop (struct hns_roce_dev*,scalar_t__) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 size_t hns_roce_hem_addr (struct hns_roce_hem_iter*) ; 
 int /*<<< orphan*/  hns_roce_hem_first (struct hns_roce_hem*,struct hns_roce_hem_iter*) ; 
 int /*<<< orphan*/  hns_roce_hem_last (struct hns_roce_hem_iter*) ; 
 int /*<<< orphan*/  hns_roce_hem_next (struct hns_roce_hem_iter*) ; 

__attribute__((used)) static int hns_roce_v2_set_hem(struct hns_roce_dev *hr_dev,
			       struct hns_roce_hem_table *table, int obj,
			       int step_idx)
{
	struct hns_roce_cmd_mailbox *mailbox;
	struct hns_roce_hem_iter iter;
	struct hns_roce_hem_mhop mhop;
	struct hns_roce_hem *hem;
	unsigned long mhop_obj = obj;
	int i, j, k;
	int ret = 0;
	u64 hem_idx = 0;
	u64 l1_idx = 0;
	u64 bt_ba = 0;
	u32 chunk_ba_num;
	u32 hop_num;
	int op;

	if (!hns_roce_check_whether_mhop(hr_dev, table->type))
		return 0;

	hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, &mhop);
	i = mhop.l0_idx;
	j = mhop.l1_idx;
	k = mhop.l2_idx;
	hop_num = mhop.hop_num;
	chunk_ba_num = mhop.bt_chunk_size / 8;

	if (hop_num == 2) {
		hem_idx = i * chunk_ba_num * chunk_ba_num + j * chunk_ba_num +
			  k;
		l1_idx = i * chunk_ba_num + j;
	} else if (hop_num == 1) {
		hem_idx = i * chunk_ba_num + j;
	} else if (hop_num == HNS_ROCE_HOP_NUM_0) {
		hem_idx = i;
	}

	op = get_op_for_set_hem(hr_dev, table->type, step_idx);
	if (op == -EINVAL)
		return 0;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	if (table->type == HEM_TYPE_SCCC)
		obj = mhop.l0_idx;

	if (check_whether_last_step(hop_num, step_idx)) {
		hem = table->hem[hem_idx];
		for (hns_roce_hem_first(hem, &iter);
		     !hns_roce_hem_last(&iter); hns_roce_hem_next(&iter)) {
			bt_ba = hns_roce_hem_addr(&iter);

			/* configure the ba, tag, and op */
			ret = hns_roce_cmd_mbox(hr_dev, bt_ba, mailbox->dma,
						obj, 0, op,
						HNS_ROCE_CMD_TIMEOUT_MSECS);
		}
	} else {
		if (step_idx == 0)
			bt_ba = table->bt_l0_dma_addr[i];
		else if (step_idx == 1 && hop_num == 2)
			bt_ba = table->bt_l1_dma_addr[l1_idx];

		/* configure the ba, tag, and op */
		ret = hns_roce_cmd_mbox(hr_dev, bt_ba, mailbox->dma, obj,
					0, op, HNS_ROCE_CMD_TIMEOUT_MSECS);
	}

	hns_roce_free_cmd_mailbox(hr_dev, mailbox);
	return ret;
}