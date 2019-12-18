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
typedef  size_t u32 ;
struct i40iw_qp_uk {size_t max_rq_frag_cnt; int rwqe_polarity; int /*<<< orphan*/ * rq_wrid_array; } ;
struct i40iw_post_rq_info {size_t num_sges; TYPE_1__* sg_list; int /*<<< orphan*/  wr_id; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_ADDFRAGCNT ; 
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 int I40IW_ERR_INVALID_FRAG_COUNT ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int* i40iw_qp_get_next_recv_wqe (struct i40iw_qp_uk*,size_t*) ; 
 int /*<<< orphan*/  i40iw_set_fragment (int*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static enum i40iw_status_code i40iw_post_receive(struct i40iw_qp_uk *qp,
						 struct i40iw_post_rq_info *info)
{
	u64 *wqe;
	u64 header;
	u32 total_size = 0, wqe_idx, i, byte_off;

	if (qp->max_rq_frag_cnt < info->num_sges)
		return I40IW_ERR_INVALID_FRAG_COUNT;
	for (i = 0; i < info->num_sges; i++)
		total_size += info->sg_list[i].len;
	wqe = i40iw_qp_get_next_recv_wqe(qp, &wqe_idx);
	if (!wqe)
		return I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	qp->rq_wrid_array[wqe_idx] = info->wr_id;
	set_64bit_val(wqe, 16, 0);

	header = LS_64((info->num_sges > 1 ? (info->num_sges - 1) : 0),
		       I40IWQPSQ_ADDFRAGCNT) |
	    LS_64(qp->rwqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, info->sg_list);

	for (i = 1, byte_off = 32; i < info->num_sges; i++) {
		i40iw_set_fragment(wqe, byte_off, &info->sg_list[i]);
		byte_off += 16;
	}

	wmb(); /* make sure WQE is populated before valid bit is set */

	set_64bit_val(wqe, 24, header);

	return 0;
}