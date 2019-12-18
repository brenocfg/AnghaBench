#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_reg_ns_stag_info {int stag_idx; int chunk_size; int /*<<< orphan*/  reg_addr_pa; int /*<<< orphan*/  first_pm_pbl_index; int /*<<< orphan*/  page_size; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  access_rights; int /*<<< orphan*/  total_len; scalar_t__ stag_key; void* va; } ;
struct TYPE_10__ {int /*<<< orphan*/  pd_id; } ;
struct i40iw_pd {TYPE_2__ sc_pd; } ;
struct TYPE_12__ {int /*<<< orphan*/  idx; } ;
struct TYPE_13__ {TYPE_4__ root; } ;
struct TYPE_11__ {int /*<<< orphan*/  idx; } ;
struct i40iw_pble_alloc {scalar_t__ level; TYPE_5__ level2; TYPE_3__ level1; } ;
struct i40iw_pbl {scalar_t__ pbl_allocated; scalar_t__ user_base; struct i40iw_pble_alloc pble_alloc; } ;
struct TYPE_9__ {int /*<<< orphan*/  pd; } ;
struct i40iw_mr {int stag; int /*<<< orphan*/ * pgaddrmem; int /*<<< orphan*/  page_size; int /*<<< orphan*/  length; TYPE_1__ ibmr; struct i40iw_pbl iwpbl; } ;
struct i40iw_device {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  cqp; } ;
struct TYPE_14__ {uintptr_t scratch; int /*<<< orphan*/ * dev; struct i40iw_reg_ns_stag_info info; } ;
struct TYPE_15__ {TYPE_6__ mr_reg_non_shared; } ;
struct TYPE_16__ {TYPE_7__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_8__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I40IW_ADDR_TYPE_VA_BASED ; 
 int I40IW_CQPSQ_STAG_IDX_SHIFT ; 
 scalar_t__ I40IW_LEVEL_1 ; 
 int /*<<< orphan*/  OP_MR_REG_NON_SHARED ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  memset (struct i40iw_reg_ns_stag_info*,int /*<<< orphan*/ ,int) ; 
 struct i40iw_pd* to_iwpd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_hwreg_mr(struct i40iw_device *iwdev,
			  struct i40iw_mr *iwmr,
			  u16 access)
{
	struct i40iw_pbl *iwpbl = &iwmr->iwpbl;
	struct i40iw_reg_ns_stag_info *stag_info;
	struct i40iw_pd *iwpd = to_iwpd(iwmr->ibmr.pd);
	struct i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	enum i40iw_status_code status;
	int err = 0;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request)
		return -ENOMEM;

	cqp_info = &cqp_request->info;
	stag_info = &cqp_info->in.u.mr_reg_non_shared.info;
	memset(stag_info, 0, sizeof(*stag_info));
	stag_info->va = (void *)(unsigned long)iwpbl->user_base;
	stag_info->stag_idx = iwmr->stag >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	stag_info->stag_key = (u8)iwmr->stag;
	stag_info->total_len = iwmr->length;
	stag_info->access_rights = access;
	stag_info->pd_id = iwpd->sc_pd.pd_id;
	stag_info->addr_type = I40IW_ADDR_TYPE_VA_BASED;
	stag_info->page_size = iwmr->page_size;

	if (iwpbl->pbl_allocated) {
		if (palloc->level == I40IW_LEVEL_1) {
			stag_info->first_pm_pbl_index = palloc->level1.idx;
			stag_info->chunk_size = 1;
		} else {
			stag_info->first_pm_pbl_index = palloc->level2.root.idx;
			stag_info->chunk_size = 3;
		}
	} else {
		stag_info->reg_addr_pa = iwmr->pgaddrmem[0];
	}

	cqp_info->cqp_cmd = OP_MR_REG_NON_SHARED;
	cqp_info->post_sq = 1;
	cqp_info->in.u.mr_reg_non_shared.dev = &iwdev->sc_dev;
	cqp_info->in.u.mr_reg_non_shared.scratch = (uintptr_t)cqp_request;

	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status) {
		err = -ENOMEM;
		i40iw_pr_err("CQP-OP MR Reg fail");
	}
	return err;
}