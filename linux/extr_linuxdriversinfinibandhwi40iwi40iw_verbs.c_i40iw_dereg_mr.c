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
typedef  int /*<<< orphan*/  u32 ;
struct ib_pd {TYPE_1__* uobject; } ;
struct ib_mr {int /*<<< orphan*/  rkey; int /*<<< orphan*/  device; struct ib_pd* pd; } ;
struct i40iw_ucontext {int dummy; } ;
struct TYPE_7__ {int pd_id; } ;
struct i40iw_pd {TYPE_2__ sc_pd; } ;
struct i40iw_pble_alloc {int dummy; } ;
struct i40iw_pbl {scalar_t__ pbl_allocated; struct i40iw_pble_alloc pble_alloc; } ;
struct i40iw_mr {scalar_t__ type; int /*<<< orphan*/  stag; scalar_t__ region; struct i40iw_pbl iwpbl; } ;
struct i40iw_device {int /*<<< orphan*/  pble_rsrc; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  cqp; } ;
struct i40iw_dealloc_stag_info {int mr; int dealloc_pbl; int /*<<< orphan*/  stag_idx; int /*<<< orphan*/  pd_id; } ;
struct TYPE_8__ {uintptr_t scratch; int /*<<< orphan*/ * dev; struct i40iw_dealloc_stag_info info; } ;
struct TYPE_9__ {TYPE_3__ dealloc_stag; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_5__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I40IW_CQPSQ_STAG_IDX_SHIFT ; 
 scalar_t__ IW_MEMREG_TYPE_MEM ; 
 scalar_t__ IW_MEMREG_TYPE_QP ; 
 int /*<<< orphan*/  OP_DEALLOC_STAG ; 
 int /*<<< orphan*/  RS_64_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  i40iw_del_memlist (struct i40iw_mr*,struct i40iw_ucontext*) ; 
 int /*<<< orphan*/  i40iw_free_pble (int /*<<< orphan*/ ,struct i40iw_pble_alloc*) ; 
 int /*<<< orphan*/  i40iw_free_stag (struct i40iw_device*,int /*<<< orphan*/ ) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rem_pdusecount (struct i40iw_pd*,struct i40iw_device*) ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct i40iw_mr*) ; 
 int /*<<< orphan*/  memset (struct i40iw_dealloc_stag_info*,int /*<<< orphan*/ ,int) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 
 struct i40iw_mr* to_iwmr (struct ib_mr*) ; 
 struct i40iw_pd* to_iwpd (struct ib_pd*) ; 
 struct i40iw_ucontext* to_ucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_dereg_mr(struct ib_mr *ib_mr)
{
	struct ib_pd *ibpd = ib_mr->pd;
	struct i40iw_pd *iwpd = to_iwpd(ibpd);
	struct i40iw_mr *iwmr = to_iwmr(ib_mr);
	struct i40iw_device *iwdev = to_iwdev(ib_mr->device);
	enum i40iw_status_code status;
	struct i40iw_dealloc_stag_info *info;
	struct i40iw_pbl *iwpbl = &iwmr->iwpbl;
	struct i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	u32 stag_idx;

	if (iwmr->region)
		ib_umem_release(iwmr->region);

	if (iwmr->type != IW_MEMREG_TYPE_MEM) {
		if (ibpd->uobject) {
			struct i40iw_ucontext *ucontext;

			ucontext = to_ucontext(ibpd->uobject->context);
			i40iw_del_memlist(iwmr, ucontext);
		}
		if (iwpbl->pbl_allocated && iwmr->type != IW_MEMREG_TYPE_QP)
			i40iw_free_pble(iwdev->pble_rsrc, palloc);
		kfree(iwmr);
		return 0;
	}

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request)
		return -ENOMEM;

	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.dealloc_stag.info;
	memset(info, 0, sizeof(*info));

	info->pd_id = cpu_to_le32(iwpd->sc_pd.pd_id & 0x00007fff);
	info->stag_idx = RS_64_1(ib_mr->rkey, I40IW_CQPSQ_STAG_IDX_SHIFT);
	stag_idx = info->stag_idx;
	info->mr = true;
	if (iwpbl->pbl_allocated)
		info->dealloc_pbl = true;

	cqp_info->cqp_cmd = OP_DEALLOC_STAG;
	cqp_info->post_sq = 1;
	cqp_info->in.u.dealloc_stag.dev = &iwdev->sc_dev;
	cqp_info->in.u.dealloc_stag.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP-OP dealloc failed for stag_idx = 0x%x\n", stag_idx);
	i40iw_rem_pdusecount(iwpd, iwdev);
	i40iw_free_stag(iwdev, iwmr->stag);
	if (iwpbl->pbl_allocated)
		i40iw_free_pble(iwdev->pble_rsrc, palloc);
	kfree(iwmr);
	return 0;
}