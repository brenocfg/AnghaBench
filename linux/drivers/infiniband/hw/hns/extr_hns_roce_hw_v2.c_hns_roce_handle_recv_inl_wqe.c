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
typedef  int u32 ;
struct ib_wc {int byte_len; int /*<<< orphan*/  status; } ;
struct hns_roce_v2_cqe {int /*<<< orphan*/  byte_4; } ;
struct hns_roce_rinl_sge {scalar_t__ addr; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_2__* wqe_list; } ;
struct TYPE_4__ {int wqe_cnt; } ;
struct hns_roce_qp {TYPE_3__ rq_inl_buf; TYPE_1__ rq; } ;
struct TYPE_5__ {int sge_cnt; struct hns_roce_rinl_sge* sg_list; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IB_WC_LOC_LEN_ERR ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_WQE_INDX_M ; 
 int /*<<< orphan*/  V2_CQE_BYTE_4_WQE_INDX_S ; 
 void* get_recv_wqe (struct hns_roce_qp*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_handle_recv_inl_wqe(struct hns_roce_v2_cqe *cqe,
						    struct hns_roce_qp **cur_qp,
						    struct ib_wc *wc)
{
	struct hns_roce_rinl_sge *sge_list;
	u32 wr_num, wr_cnt, sge_num;
	u32 sge_cnt, data_len, size;
	void *wqe_buf;

	wr_num = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_WQE_INDX_M,
				V2_CQE_BYTE_4_WQE_INDX_S) & 0xffff;
	wr_cnt = wr_num & ((*cur_qp)->rq.wqe_cnt - 1);

	sge_list = (*cur_qp)->rq_inl_buf.wqe_list[wr_cnt].sg_list;
	sge_num = (*cur_qp)->rq_inl_buf.wqe_list[wr_cnt].sge_cnt;
	wqe_buf = get_recv_wqe(*cur_qp, wr_cnt);
	data_len = wc->byte_len;

	for (sge_cnt = 0; (sge_cnt < sge_num) && (data_len); sge_cnt++) {
		size = min(sge_list[sge_cnt].len, data_len);
		memcpy((void *)sge_list[sge_cnt].addr, wqe_buf, size);

		data_len -= size;
		wqe_buf += size;
	}

	if (data_len) {
		wc->status = IB_WC_LOC_LEN_ERR;
		return -EAGAIN;
	}

	return 0;
}