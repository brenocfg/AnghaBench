#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct i40iw_sq_uk_wr_trk_info {int dummy; } ;
struct i40iw_qp_uk_init_info {int sq_size; int rq_size; int /*<<< orphan*/  qp_id; TYPE_3__* rq; int /*<<< orphan*/  shadow_area; TYPE_3__* sq; struct i40iw_sq_uk_wr_trk_info* sq_wrtrk_array; int /*<<< orphan*/ * rq_wrid_array; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_sq_frag_cnt; } ;
struct i40iw_qp_init_info {scalar_t__ rq_pa; scalar_t__ shadow_area_pa; int /*<<< orphan*/  sq_pa; struct i40iw_qp_uk_init_info qp_uk_init_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_num; } ;
struct i40iw_dma_mem {int /*<<< orphan*/  pa; TYPE_3__* va; } ;
struct TYPE_5__ {scalar_t__ wrid_mem; struct i40iw_dma_mem dma_mem; } ;
struct i40iw_qp {TYPE_4__ ibqp; TYPE_1__ kqp; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct i40iw_device {TYPE_2__ sc_dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_7__ {int /*<<< orphan*/  elem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I40IW_MAX_RQ_WQE_SHIFT ; 
 int I40IW_QP_WQE_MIN_SIZE ; 
 int I40IW_SHADOW_AREA_SIZE ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,struct i40iw_dma_mem*,int,int) ; 
 int i40iw_get_rqdepth (int,int,int*) ; 
 int i40iw_get_sqdepth (int,int,int*) ; 
 int /*<<< orphan*/  i40iw_get_wqe_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (struct i40iw_sq_uk_wr_trk_info*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_setup_kmode_qp(struct i40iw_device *iwdev,
				struct i40iw_qp *iwqp,
				struct i40iw_qp_init_info *info)
{
	struct i40iw_dma_mem *mem = &iwqp->kqp.dma_mem;
	u32 sqdepth, rqdepth;
	u8 sqshift;
	u32 size;
	enum i40iw_status_code status;
	struct i40iw_qp_uk_init_info *ukinfo = &info->qp_uk_init_info;

	i40iw_get_wqe_shift(ukinfo->max_sq_frag_cnt, ukinfo->max_inline_data, &sqshift);
	status = i40iw_get_sqdepth(ukinfo->sq_size, sqshift, &sqdepth);
	if (status)
		return -ENOMEM;

	status = i40iw_get_rqdepth(ukinfo->rq_size, I40IW_MAX_RQ_WQE_SHIFT, &rqdepth);
	if (status)
		return -ENOMEM;

	size = sqdepth * sizeof(struct i40iw_sq_uk_wr_trk_info) + (rqdepth << 3);
	iwqp->kqp.wrid_mem = kzalloc(size, GFP_KERNEL);

	ukinfo->sq_wrtrk_array = (struct i40iw_sq_uk_wr_trk_info *)iwqp->kqp.wrid_mem;
	if (!ukinfo->sq_wrtrk_array)
		return -ENOMEM;

	ukinfo->rq_wrid_array = (u64 *)&ukinfo->sq_wrtrk_array[sqdepth];

	size = (sqdepth + rqdepth) * I40IW_QP_WQE_MIN_SIZE;
	size += (I40IW_SHADOW_AREA_SIZE << 3);

	status = i40iw_allocate_dma_mem(iwdev->sc_dev.hw, mem, size, 256);
	if (status) {
		kfree(ukinfo->sq_wrtrk_array);
		ukinfo->sq_wrtrk_array = NULL;
		return -ENOMEM;
	}

	ukinfo->sq = mem->va;
	info->sq_pa = mem->pa;

	ukinfo->rq = &ukinfo->sq[sqdepth];
	info->rq_pa = info->sq_pa + (sqdepth * I40IW_QP_WQE_MIN_SIZE);

	ukinfo->shadow_area = ukinfo->rq[rqdepth].elem;
	info->shadow_area_pa = info->rq_pa + (rqdepth * I40IW_QP_WQE_MIN_SIZE);

	ukinfo->sq_size = sqdepth >> sqshift;
	ukinfo->rq_size = rqdepth >> I40IW_MAX_RQ_WQE_SHIFT;
	ukinfo->qp_id = iwqp->ibqp.qp_num;
	return 0;
}