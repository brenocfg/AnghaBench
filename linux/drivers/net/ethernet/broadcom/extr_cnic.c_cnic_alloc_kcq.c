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
typedef  int u64 ;
struct kcqe {int dummy; } ;
struct TYPE_2__ {int* pg_map_arr; scalar_t__ pg_arr; } ;
struct kcq_info {TYPE_1__ dma; int /*<<< orphan*/  hw_idx; int /*<<< orphan*/  next_idx; struct kcqe** kcq; } ;
struct cnic_dev {int dummy; } ;
struct bnx2x_bd_chain_next {int addr_hi; int addr_lo; } ;

/* Variables and functions */
 int KCQ_PAGE_CNT ; 
 size_t MAX_KCQE_CNT ; 
 int cnic_alloc_dma (struct cnic_dev*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  cnic_bnx2_hw_idx ; 
 int /*<<< orphan*/  cnic_bnx2_next_idx ; 
 int /*<<< orphan*/  cnic_bnx2x_hw_idx ; 
 int /*<<< orphan*/  cnic_bnx2x_next_idx ; 

__attribute__((used)) static int cnic_alloc_kcq(struct cnic_dev *dev, struct kcq_info *info,
			  bool use_pg_tbl)
{
	int err, i, use_page_tbl = 0;
	struct kcqe **kcq;

	if (use_pg_tbl)
		use_page_tbl = 1;

	err = cnic_alloc_dma(dev, &info->dma, KCQ_PAGE_CNT, use_page_tbl);
	if (err)
		return err;

	kcq = (struct kcqe **) info->dma.pg_arr;
	info->kcq = kcq;

	info->next_idx = cnic_bnx2_next_idx;
	info->hw_idx = cnic_bnx2_hw_idx;
	if (use_pg_tbl)
		return 0;

	info->next_idx = cnic_bnx2x_next_idx;
	info->hw_idx = cnic_bnx2x_hw_idx;

	for (i = 0; i < KCQ_PAGE_CNT; i++) {
		struct bnx2x_bd_chain_next *next =
			(struct bnx2x_bd_chain_next *) &kcq[i][MAX_KCQE_CNT];
		int j = i + 1;

		if (j >= KCQ_PAGE_CNT)
			j = 0;
		next->addr_hi = (u64) info->dma.pg_map_arr[j] >> 32;
		next->addr_lo = info->dma.pg_map_arr[j] & 0xffffffff;
	}
	return 0;
}