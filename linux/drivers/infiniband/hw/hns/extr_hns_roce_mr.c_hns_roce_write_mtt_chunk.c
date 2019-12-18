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
typedef  int u64 ;
typedef  int u32 ;
struct hns_roce_mtt {int mtt_type; scalar_t__ first_seg; } ;
struct hns_roce_hem_table {int dummy; } ;
struct TYPE_4__ {int mtt_ba_pg_sz; int cqe_ba_pg_sz; int srqwqe_ba_pg_sz; int idx_ba_pg_sz; int /*<<< orphan*/  mtt_hop_num; } ;
struct TYPE_3__ {struct hns_roce_hem_table mtt_idx_table; struct hns_roce_hem_table mtt_srqwqe_table; struct hns_roce_hem_table mtt_cqe_table; struct hns_roce_hem_table mtt_table; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__ mr_table; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HNS_ROCE_MTT_ENTRY_PER_SEG ; 
#define  MTT_TYPE_CQE 131 
#define  MTT_TYPE_IDX 130 
#define  MTT_TYPE_SRQWQE 129 
#define  MTT_TYPE_WQE 128 
 int PAGE_ADDR_SHIFT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/ * hns_roce_table_find (struct hns_roce_dev*,struct hns_roce_hem_table*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_write_mtt_chunk(struct hns_roce_dev *hr_dev,
				    struct hns_roce_mtt *mtt, u32 start_index,
				    u32 npages, u64 *page_list)
{
	struct hns_roce_hem_table *table;
	dma_addr_t dma_handle;
	__le64 *mtts;
	u32 bt_page_size;
	u32 i;

	switch (mtt->mtt_type) {
	case MTT_TYPE_WQE:
		table = &hr_dev->mr_table.mtt_table;
		bt_page_size = 1 << (hr_dev->caps.mtt_ba_pg_sz + PAGE_SHIFT);
		break;
	case MTT_TYPE_CQE:
		table = &hr_dev->mr_table.mtt_cqe_table;
		bt_page_size = 1 << (hr_dev->caps.cqe_ba_pg_sz + PAGE_SHIFT);
		break;
	case MTT_TYPE_SRQWQE:
		table = &hr_dev->mr_table.mtt_srqwqe_table;
		bt_page_size = 1 << (hr_dev->caps.srqwqe_ba_pg_sz + PAGE_SHIFT);
		break;
	case MTT_TYPE_IDX:
		table = &hr_dev->mr_table.mtt_idx_table;
		bt_page_size = 1 << (hr_dev->caps.idx_ba_pg_sz + PAGE_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	/* All MTTs must fit in the same page */
	if (start_index / (bt_page_size / sizeof(u64)) !=
		(start_index + npages - 1) / (bt_page_size / sizeof(u64)))
		return -EINVAL;

	if (start_index & (HNS_ROCE_MTT_ENTRY_PER_SEG - 1))
		return -EINVAL;

	mtts = hns_roce_table_find(hr_dev, table,
				mtt->first_seg +
				start_index / HNS_ROCE_MTT_ENTRY_PER_SEG,
				&dma_handle);
	if (!mtts)
		return -ENOMEM;

	/* Save page addr, low 12 bits : 0 */
	for (i = 0; i < npages; ++i) {
		if (!hr_dev->caps.mtt_hop_num)
			mtts[i] = cpu_to_le64(page_list[i] >> PAGE_ADDR_SHIFT);
		else
			mtts[i] = cpu_to_le64(page_list[i]);
	}

	return 0;
}