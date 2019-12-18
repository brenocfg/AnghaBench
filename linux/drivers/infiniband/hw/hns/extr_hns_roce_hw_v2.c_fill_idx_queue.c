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
struct hns_roce_idx_que {int entry_sz; int /*<<< orphan*/  idx_buf; } ;

/* Variables and functions */
 scalar_t__ hns_roce_buf_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill_idx_queue(struct hns_roce_idx_que *idx_que,
			   int cur_idx, int wqe_idx)
{
	unsigned int *addr;

	addr = (unsigned int *)hns_roce_buf_offset(&idx_que->idx_buf,
						   cur_idx * idx_que->entry_sz);
	*addr = wqe_idx;
}