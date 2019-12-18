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
typedef  int u16 ;
struct kcqe {int kcqe_op_flag; } ;
struct kcq_info {int sw_prod_idx; int* hw_prod_idx_ptr; int (* hw_idx ) (int) ;int (* next_idx ) (int) ;struct kcqe** kcq; } ;
struct cnic_local {struct kcqe** completed_kcq; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int KCQE_FLAGS_NEXT ; 
 size_t KCQ_IDX (int) ; 
 size_t KCQ_PG (int) ; 
 int MAX_COMPLETED_KCQE ; 
 int MAX_KCQ_IDX ; 
 scalar_t__ likely (int) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 

__attribute__((used)) static int cnic_get_kcqes(struct cnic_dev *dev, struct kcq_info *info)
{
	struct cnic_local *cp = dev->cnic_priv;
	u16 i, ri, hw_prod, last;
	struct kcqe *kcqe;
	int kcqe_cnt = 0, last_cnt = 0;

	i = ri = last = info->sw_prod_idx;
	ri &= MAX_KCQ_IDX;
	hw_prod = *info->hw_prod_idx_ptr;
	hw_prod = info->hw_idx(hw_prod);

	while ((i != hw_prod) && (kcqe_cnt < MAX_COMPLETED_KCQE)) {
		kcqe = &info->kcq[KCQ_PG(ri)][KCQ_IDX(ri)];
		cp->completed_kcq[kcqe_cnt++] = kcqe;
		i = info->next_idx(i);
		ri = i & MAX_KCQ_IDX;
		if (likely(!(kcqe->kcqe_op_flag & KCQE_FLAGS_NEXT))) {
			last_cnt = kcqe_cnt;
			last = i;
		}
	}

	info->sw_prod_idx = last;
	return last_cnt;
}