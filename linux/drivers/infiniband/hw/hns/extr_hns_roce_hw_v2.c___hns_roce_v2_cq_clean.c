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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hns_roce_v2_cqe {int /*<<< orphan*/  byte_4; int /*<<< orphan*/  byte_16; } ;
struct hns_roce_srq {int dummy; } ;
struct TYPE_2__ {int cqe; } ;
struct hns_roce_cq {int cons_index; TYPE_1__ ib_cq; } ;

/* Variables and functions */
 int HNS_ROCE_V2_CQE_QPN_MASK ; 
 int /*<<< orphan*/  V2_CQE_BYTE_16_LCL_QPN_M ; 
 int /*<<< orphan*/  V2_CQE_BYTE_16_LCL_QPN_S ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_OWNER_S ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_S_R_S ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_WQE_INDX_M ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_WQE_INDX_S ; 
 struct hns_roce_v2_cqe* get_cqe_v2 (struct hns_roce_cq*,int) ; 
 scalar_t__ get_sw_cqe_v2 (struct hns_roce_cq*,int) ; 
 int /*<<< orphan*/  hns_roce_free_srq_wqe (struct hns_roce_srq*,int) ; 
 int /*<<< orphan*/  hns_roce_v2_cq_set_ci (struct hns_roce_cq*,int) ; 
 int /*<<< orphan*/  memcpy (struct hns_roce_v2_cqe*,struct hns_roce_v2_cqe*,int) ; 
 scalar_t__ roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __hns_roce_v2_cq_clean(struct hns_roce_cq *hr_cq, u32 qpn,
				   struct hns_roce_srq *srq)
{
	struct hns_roce_v2_cqe *cqe, *dest;
	u32 prod_index;
	int nfreed = 0;
	int wqe_index;
	u8 owner_bit;

	for (prod_index = hr_cq->cons_index; get_sw_cqe_v2(hr_cq, prod_index);
	     ++prod_index) {
		if (prod_index > hr_cq->cons_index + hr_cq->ib_cq.cqe)
			break;
	}

	/*
	 * Now backwards through the CQ, removing CQ entries
	 * that match our QP by overwriting them with next entries.
	 */
	while ((int) --prod_index - (int) hr_cq->cons_index >= 0) {
		cqe = get_cqe_v2(hr_cq, prod_index & hr_cq->ib_cq.cqe);
		if ((roce_get_field(cqe->byte_16, V2_CQE_BYTE_16_LCL_QPN_M,
				    V2_CQE_BYTE_16_LCL_QPN_S) &
				    HNS_ROCE_V2_CQE_QPN_MASK) == qpn) {
			if (srq &&
			    roce_get_bit(cqe->byte_4, V2_CQE_BYTE_4_S_R_S)) {
				wqe_index = roce_get_field(cqe->byte_4,
						     V2_CQE_BYTE_4_WQE_INDX_M,
						     V2_CQE_BYTE_4_WQE_INDX_S);
				hns_roce_free_srq_wqe(srq, wqe_index);
			}
			++nfreed;
		} else if (nfreed) {
			dest = get_cqe_v2(hr_cq, (prod_index + nfreed) &
					  hr_cq->ib_cq.cqe);
			owner_bit = roce_get_bit(dest->byte_4,
						 V2_CQE_BYTE_4_OWNER_S);
			memcpy(dest, cqe, sizeof(*cqe));
			roce_set_bit(dest->byte_4, V2_CQE_BYTE_4_OWNER_S,
				     owner_bit);
		}
	}

	if (nfreed) {
		hr_cq->cons_index += nfreed;
		/*
		 * Make sure update of buffer contents is done before
		 * updating consumer index.
		 */
		wmb();
		hns_roce_v2_cq_set_ci(hr_cq, hr_cq->cons_index);
	}
}