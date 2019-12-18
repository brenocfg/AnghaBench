#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pd_id; } ;
struct i40iw_pd {TYPE_2__ sc_pd; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd; } ;
struct i40iw_mr {int stag; int /*<<< orphan*/  length; TYPE_1__ ibmr; } ;
struct i40iw_device {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  cqp; } ;
struct i40iw_allocate_stag_info {int stag_idx; int remote_access; int /*<<< orphan*/  total_len; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  page_size; } ;
struct TYPE_8__ {uintptr_t scratch; int /*<<< orphan*/ * dev; struct i40iw_allocate_stag_info info; } ;
struct TYPE_9__ {TYPE_3__ alloc_stag; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_5__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int ENOMEM ; 
 int I40IW_CQPSQ_STAG_IDX_SHIFT ; 
 int /*<<< orphan*/  OP_ALLOC_STAG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  memset (struct i40iw_allocate_stag_info*,int /*<<< orphan*/ ,int) ; 
 struct i40iw_pd* to_iwpd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_hw_alloc_stag(struct i40iw_device *iwdev, struct i40iw_mr *iwmr)
{
	struct i40iw_allocate_stag_info *info;
	struct i40iw_pd *iwpd = to_iwpd(iwmr->ibmr.pd);
	enum i40iw_status_code status;
	int err = 0;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request)
		return -ENOMEM;

	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.alloc_stag.info;
	memset(info, 0, sizeof(*info));
	info->page_size = PAGE_SIZE;
	info->stag_idx = iwmr->stag >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	info->pd_id = iwpd->sc_pd.pd_id;
	info->total_len = iwmr->length;
	info->remote_access = true;
	cqp_info->cqp_cmd = OP_ALLOC_STAG;
	cqp_info->post_sq = 1;
	cqp_info->in.u.alloc_stag.dev = &iwdev->sc_dev;
	cqp_info->in.u.alloc_stag.scratch = (uintptr_t)cqp_request;

	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status) {
		err = -ENOMEM;
		i40iw_pr_err("CQP-OP MR Reg fail");
	}
	return err;
}