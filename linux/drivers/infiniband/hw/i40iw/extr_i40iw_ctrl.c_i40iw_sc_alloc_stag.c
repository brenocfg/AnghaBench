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
typedef  int u64 ;
struct i40iw_sc_dev {struct i40iw_sc_cqp* cqp; } ;
struct i40iw_sc_cqp {int polarity; } ;
struct i40iw_allocate_stag_info {int page_size; int pd_id; int total_len; int stag_idx; int hmc_fcn_index; int access_rights; int chunk_size; int remote_access; int use_hmc_fcn_index; int use_pf_rid; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
typedef  enum i40iw_page_size { ____Placeholder_i40iw_page_size } i40iw_page_size ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_ARIGHTS ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_HMCFNIDX ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_HPAGESIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_IDX ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_LPBLSIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_MR ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_PDID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_REMACCENABLED ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_STAGLEN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_USEHMCFNIDX ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_USEPFRID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_ALLOC_STAG ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int I40IW_PAGE_SIZE_2M ; 
 int I40IW_PAGE_SIZE_4K ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_alloc_stag(
				struct i40iw_sc_dev *dev,
				struct i40iw_allocate_stag_info *info,
				u64 scratch,
				bool post_sq)
{
	u64 *wqe;
	struct i40iw_sc_cqp *cqp;
	u64 header;
	enum i40iw_page_size page_size;

	page_size = (info->page_size == 0x200000) ? I40IW_PAGE_SIZE_2M : I40IW_PAGE_SIZE_4K;
	cqp = dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	set_64bit_val(wqe,
		      8,
		      LS_64(info->pd_id, I40IW_CQPSQ_STAG_PDID) |
		      LS_64(info->total_len, I40IW_CQPSQ_STAG_STAGLEN));
	set_64bit_val(wqe,
		      16,
		      LS_64(info->stag_idx, I40IW_CQPSQ_STAG_IDX));
	set_64bit_val(wqe,
		      40,
		      LS_64(info->hmc_fcn_index, I40IW_CQPSQ_STAG_HMCFNIDX));

	header = LS_64(I40IW_CQP_OP_ALLOC_STAG, I40IW_CQPSQ_OPCODE) |
		 LS_64(1, I40IW_CQPSQ_STAG_MR) |
		 LS_64(info->access_rights, I40IW_CQPSQ_STAG_ARIGHTS) |
		 LS_64(info->chunk_size, I40IW_CQPSQ_STAG_LPBLSIZE) |
		 LS_64(page_size, I40IW_CQPSQ_STAG_HPAGESIZE) |
		 LS_64(info->remote_access, I40IW_CQPSQ_STAG_REMACCENABLED) |
		 LS_64(info->use_hmc_fcn_index, I40IW_CQPSQ_STAG_USEHMCFNIDX) |
		 LS_64(info->use_pf_rid, I40IW_CQPSQ_STAG_USEPFRID) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(dev, I40IW_DEBUG_WQE, "ALLOC_STAG WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}