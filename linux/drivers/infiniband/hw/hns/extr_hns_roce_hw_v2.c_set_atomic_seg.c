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
struct TYPE_2__ {scalar_t__ opcode; } ;
struct ib_atomic_wr {int /*<<< orphan*/  compare_add; int /*<<< orphan*/  swap; TYPE_1__ wr; } ;
struct hns_roce_wqe_atomic_seg {void* cmp_data; void* fetchadd_swap_data; } ;

/* Variables and functions */
 scalar_t__ IB_WR_ATOMIC_CMP_AND_SWP ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_atomic_seg(struct hns_roce_wqe_atomic_seg *aseg,
			   const struct ib_atomic_wr *wr)
{
	if (wr->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP) {
		aseg->fetchadd_swap_data = cpu_to_le64(wr->swap);
		aseg->cmp_data  = cpu_to_le64(wr->compare_add);
	} else {
		aseg->fetchadd_swap_data = cpu_to_le64(wr->compare_add);
		aseg->cmp_data  = 0;
	}
}