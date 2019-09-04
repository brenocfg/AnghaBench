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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hns_roce_srq {int dummy; } ;
struct hns_roce_cqe {int /*<<< orphan*/  cqe_byte_4; int /*<<< orphan*/  cqe_byte_16; } ;
struct TYPE_2__ {int cqe; } ;
struct hns_roce_cq {int cons_index; TYPE_1__ ib_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQE_BYTE_16_LOCAL_QPN_M ; 
 int /*<<< orphan*/  CQE_BYTE_16_LOCAL_QPN_S ; 
 int /*<<< orphan*/  CQE_BYTE_4_OWNER_S ; 
 int HNS_ROCE_CQE_QPN_MASK ; 
 struct hns_roce_cqe* get_cqe (struct hns_roce_cq*,int) ; 
 scalar_t__ get_sw_cqe (struct hns_roce_cq*,int) ; 
 int /*<<< orphan*/  hns_roce_v1_cq_set_ci (struct hns_roce_cq*,int) ; 
 int /*<<< orphan*/  memcpy (struct hns_roce_cqe*,struct hns_roce_cqe*,int) ; 
 int /*<<< orphan*/  roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __hns_roce_v1_cq_clean(struct hns_roce_cq *hr_cq, u32 qpn,
				   struct hns_roce_srq *srq)
{
	struct hns_roce_cqe *cqe, *dest;
	u32 prod_index;
	int nfreed = 0;
	u8 owner_bit;

	for (prod_index = hr_cq->cons_index; get_sw_cqe(hr_cq, prod_index);
	     ++prod_index) {
		if (prod_index == hr_cq->cons_index + hr_cq->ib_cq.cqe)
			break;
	}

	/*
	 * Now backwards through the CQ, removing CQ entries
	 * that match our QP by overwriting them with next entries.
	 */
	while ((int) --prod_index - (int) hr_cq->cons_index >= 0) {
		cqe = get_cqe(hr_cq, prod_index & hr_cq->ib_cq.cqe);
		if ((roce_get_field(cqe->cqe_byte_16, CQE_BYTE_16_LOCAL_QPN_M,
				     CQE_BYTE_16_LOCAL_QPN_S) &
				     HNS_ROCE_CQE_QPN_MASK) == qpn) {
			/* In v1 engine, not support SRQ */
			++nfreed;
		} else if (nfreed) {
			dest = get_cqe(hr_cq, (prod_index + nfreed) &
				       hr_cq->ib_cq.cqe);
			owner_bit = roce_get_bit(dest->cqe_byte_4,
						 CQE_BYTE_4_OWNER_S);
			memcpy(dest, cqe, sizeof(*cqe));
			roce_set_bit(dest->cqe_byte_4, CQE_BYTE_4_OWNER_S,
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

		hns_roce_v1_cq_set_ci(hr_cq, hr_cq->cons_index);
	}
}