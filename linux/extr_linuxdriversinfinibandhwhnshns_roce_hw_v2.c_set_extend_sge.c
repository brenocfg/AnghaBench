#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ib_sge {int dummy; } ;
struct ib_send_wr {int num_sge; struct ib_sge* sg_list; } ;
struct hns_roce_v2_wqe_data_seg {int dummy; } ;
struct TYPE_6__ {int sge_cnt; } ;
struct TYPE_5__ {int page_shift; } ;
struct TYPE_4__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {TYPE_3__ sge; TYPE_2__ hr_buf; TYPE_1__ ibqp; } ;

/* Variables and functions */
 int HNS_ROCE_V2_UC_RC_SGE_NUM_IN_WQE ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 struct hns_roce_v2_wqe_data_seg* get_send_extend_sge (struct hns_roce_qp*,unsigned int) ; 
 uintptr_t round_up (uintptr_t,int) ; 
 int /*<<< orphan*/  set_data_seg_v2 (int /*<<< orphan*/ ,struct ib_sge*) ; 

__attribute__((used)) static void set_extend_sge(struct hns_roce_qp *qp, const struct ib_send_wr *wr,
			   unsigned int *sge_ind)
{
	struct hns_roce_v2_wqe_data_seg *dseg;
	struct ib_sge *sg;
	int num_in_wqe = 0;
	int extend_sge_num;
	int fi_sge_num;
	int se_sge_num;
	int shift;
	int i;

	if (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC)
		num_in_wqe = HNS_ROCE_V2_UC_RC_SGE_NUM_IN_WQE;
	extend_sge_num = wr->num_sge - num_in_wqe;
	sg = wr->sg_list + num_in_wqe;
	shift = qp->hr_buf.page_shift;

	/*
	 * Check whether wr->num_sge sges are in the same page. If not, we
	 * should calculate how many sges in the first page and the second
	 * page.
	 */
	dseg = get_send_extend_sge(qp, (*sge_ind) & (qp->sge.sge_cnt - 1));
	fi_sge_num = (round_up((uintptr_t)dseg, 1 << shift) -
		      (uintptr_t)dseg) /
		      sizeof(struct hns_roce_v2_wqe_data_seg);
	if (extend_sge_num > fi_sge_num) {
		se_sge_num = extend_sge_num - fi_sge_num;
		for (i = 0; i < fi_sge_num; i++) {
			set_data_seg_v2(dseg++, sg + i);
			(*sge_ind)++;
		}
		dseg = get_send_extend_sge(qp,
					   (*sge_ind) & (qp->sge.sge_cnt - 1));
		for (i = 0; i < se_sge_num; i++) {
			set_data_seg_v2(dseg++, sg + fi_sge_num + i);
			(*sge_ind)++;
		}
	} else {
		for (i = 0; i < extend_sge_num; i++) {
			set_data_seg_v2(dseg++, sg + i);
			(*sge_ind)++;
		}
	}
}