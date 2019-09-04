#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; scalar_t__ comp_vector; } ;
struct ib_cq {int dummy; } ;
struct i40iw_ucontext {int /*<<< orphan*/  cq_reg_mem_list_lock; int /*<<< orphan*/  cq_reg_mem_list; } ;
struct i40iw_sc_dev {TYPE_6__* iw_priv_cq_ops; int /*<<< orphan*/  hw; } ;
struct i40iw_sc_cq {void* back_cq; } ;
struct TYPE_12__ {scalar_t__ addr; int /*<<< orphan*/  idx; } ;
struct i40iw_cq_mr {TYPE_5__ cq_pbl; int /*<<< orphan*/  shadow; } ;
struct i40iw_pbl {scalar_t__ pbl_allocated; struct i40iw_cq_mr cq_mr; } ;
struct i40iw_device {int max_cqe; scalar_t__ ceqs_count; int /*<<< orphan*/  cqp; int /*<<< orphan*/  next_cq; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  allocated_cqs; scalar_t__ closing; struct i40iw_sc_dev sc_dev; } ;
struct i40iw_cq_uk_init_info {int cq_size; int /*<<< orphan*/  cq_id; scalar_t__ shadow_area; scalar_t__ cq_base; } ;
struct i40iw_create_cq_resp {int ceqe_mask; scalar_t__ ceq_id; int ceq_id_valid; int virtual_map; int pbl_chunk_size; int cq_size; struct i40iw_cq_uk_init_info cq_uk_init_info; int /*<<< orphan*/  cq_id; scalar_t__ cq_base_pa; scalar_t__ shadow_area_pa; int /*<<< orphan*/  first_pm_pbl_idx; scalar_t__ user_cq_buffer; int /*<<< orphan*/  type; struct i40iw_sc_dev* dev; } ;
struct i40iw_create_cq_req {int ceqe_mask; scalar_t__ ceq_id; int ceq_id_valid; int virtual_map; int pbl_chunk_size; int cq_size; struct i40iw_cq_uk_init_info cq_uk_init_info; int /*<<< orphan*/  cq_id; scalar_t__ cq_base_pa; scalar_t__ shadow_area_pa; int /*<<< orphan*/  first_pm_pbl_idx; scalar_t__ user_cq_buffer; int /*<<< orphan*/  type; struct i40iw_sc_dev* dev; } ;
struct TYPE_8__ {uintptr_t scratch; struct i40iw_sc_cq* cq; } ;
struct TYPE_9__ {TYPE_1__ cq_create; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
struct i40iw_cqe {int dummy; } ;
struct i40iw_cq_init_info {int ceqe_mask; scalar_t__ ceq_id; int ceq_id_valid; int virtual_map; int pbl_chunk_size; int cq_size; struct i40iw_cq_uk_init_info cq_uk_init_info; int /*<<< orphan*/  cq_id; scalar_t__ cq_base_pa; scalar_t__ shadow_area_pa; int /*<<< orphan*/  first_pm_pbl_idx; scalar_t__ user_cq_buffer; int /*<<< orphan*/  type; struct i40iw_sc_dev* dev; } ;
struct TYPE_14__ {scalar_t__ va; scalar_t__ pa; } ;
struct TYPE_11__ {int cqe; } ;
struct i40iw_cq {int user_mode; TYPE_7__ kmem; scalar_t__ cq_mem_size; struct i40iw_pbl* iwpbl; TYPE_4__ ibcq; int /*<<< orphan*/  lock; struct i40iw_sc_cq sc_cq; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_13__ {scalar_t__ (* cq_init ) (struct i40iw_sc_cq*,struct i40iw_create_cq_resp*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROTO ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40IW_CQ_TYPE_IWARP ; 
 int I40IW_SHADOW_AREA_SIZE ; 
 int /*<<< orphan*/  OP_CQ_CREATE ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cq_free_resources (struct i40iw_device*,struct i40iw_cq*) ; 
 int /*<<< orphan*/  i40iw_add_devusecount (struct i40iw_device*) ; 
 int i40iw_alloc_resource (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  i40iw_cq_wq_destroy (struct i40iw_device*,struct i40iw_sc_cq*) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 struct i40iw_pbl* i40iw_get_pbl (unsigned long,int /*<<< orphan*/ *) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 scalar_t__ ib_copy_from_udata (struct i40iw_create_cq_resp*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct i40iw_create_cq_resp*,int) ; 
 int /*<<< orphan*/  kfree (struct i40iw_cq*) ; 
 struct i40iw_cq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (struct i40iw_create_cq_resp*,int /*<<< orphan*/ ,int) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct i40iw_sc_cq*,struct i40iw_create_cq_resp*) ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 
 struct i40iw_ucontext* to_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static struct ib_cq *i40iw_create_cq(struct ib_device *ibdev,
				     const struct ib_cq_init_attr *attr,
				     struct ib_ucontext *context,
				     struct ib_udata *udata)
{
	struct i40iw_device *iwdev = to_iwdev(ibdev);
	struct i40iw_cq *iwcq;
	struct i40iw_pbl *iwpbl;
	u32 cq_num = 0;
	struct i40iw_sc_cq *cq;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_cq_init_info info;
	enum i40iw_status_code status;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	struct i40iw_cq_uk_init_info *ukinfo = &info.cq_uk_init_info;
	unsigned long flags;
	int err_code;
	int entries = attr->cqe;

	if (iwdev->closing)
		return ERR_PTR(-ENODEV);

	if (entries > iwdev->max_cqe)
		return ERR_PTR(-EINVAL);

	iwcq = kzalloc(sizeof(*iwcq), GFP_KERNEL);
	if (!iwcq)
		return ERR_PTR(-ENOMEM);

	memset(&info, 0, sizeof(info));

	err_code = i40iw_alloc_resource(iwdev, iwdev->allocated_cqs,
					iwdev->max_cq, &cq_num,
					&iwdev->next_cq);
	if (err_code)
		goto error;

	cq = &iwcq->sc_cq;
	cq->back_cq = (void *)iwcq;
	spin_lock_init(&iwcq->lock);

	info.dev = dev;
	ukinfo->cq_size = max(entries, 4);
	ukinfo->cq_id = cq_num;
	iwcq->ibcq.cqe = info.cq_uk_init_info.cq_size;
	info.ceqe_mask = 0;
	if (attr->comp_vector < iwdev->ceqs_count)
		info.ceq_id = attr->comp_vector;
	info.ceq_id_valid = true;
	info.ceqe_mask = 1;
	info.type = I40IW_CQ_TYPE_IWARP;
	if (context) {
		struct i40iw_ucontext *ucontext;
		struct i40iw_create_cq_req req;
		struct i40iw_cq_mr *cqmr;

		memset(&req, 0, sizeof(req));
		iwcq->user_mode = true;
		ucontext = to_ucontext(context);
		if (ib_copy_from_udata(&req, udata, sizeof(struct i40iw_create_cq_req))) {
			err_code = -EFAULT;
			goto cq_free_resources;
		}

		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		iwpbl = i40iw_get_pbl((unsigned long)req.user_cq_buffer,
				      &ucontext->cq_reg_mem_list);
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		if (!iwpbl) {
			err_code = -EPROTO;
			goto cq_free_resources;
		}

		iwcq->iwpbl = iwpbl;
		iwcq->cq_mem_size = 0;
		cqmr = &iwpbl->cq_mr;
		info.shadow_area_pa = cpu_to_le64(cqmr->shadow);
		if (iwpbl->pbl_allocated) {
			info.virtual_map = true;
			info.pbl_chunk_size = 1;
			info.first_pm_pbl_idx = cqmr->cq_pbl.idx;
		} else {
			info.cq_base_pa = cqmr->cq_pbl.addr;
		}
	} else {
		/* Kmode allocations */
		int rsize;
		int shadow;

		rsize = info.cq_uk_init_info.cq_size * sizeof(struct i40iw_cqe);
		rsize = round_up(rsize, 256);
		shadow = I40IW_SHADOW_AREA_SIZE << 3;
		status = i40iw_allocate_dma_mem(dev->hw, &iwcq->kmem,
						rsize + shadow, 256);
		if (status) {
			err_code = -ENOMEM;
			goto cq_free_resources;
		}
		ukinfo->cq_base = iwcq->kmem.va;
		info.cq_base_pa = iwcq->kmem.pa;
		info.shadow_area_pa = info.cq_base_pa + rsize;
		ukinfo->shadow_area = iwcq->kmem.va + rsize;
	}

	if (dev->iw_priv_cq_ops->cq_init(cq, &info)) {
		i40iw_pr_err("init cq fail\n");
		err_code = -EPROTO;
		goto cq_free_resources;
	}

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request) {
		err_code = -ENOMEM;
		goto cq_free_resources;
	}

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_CQ_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_create.cq = cq;
	cqp_info->in.u.cq_create.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status) {
		i40iw_pr_err("CQP-OP Create QP fail");
		err_code = -EPROTO;
		goto cq_free_resources;
	}

	if (context) {
		struct i40iw_create_cq_resp resp;

		memset(&resp, 0, sizeof(resp));
		resp.cq_id = info.cq_uk_init_info.cq_id;
		resp.cq_size = info.cq_uk_init_info.cq_size;
		if (ib_copy_to_udata(udata, &resp, sizeof(resp))) {
			i40iw_pr_err("copy to user data\n");
			err_code = -EPROTO;
			goto cq_destroy;
		}
	}

	i40iw_add_devusecount(iwdev);
	return (struct ib_cq *)iwcq;

cq_destroy:
	i40iw_cq_wq_destroy(iwdev, cq);
cq_free_resources:
	cq_free_resources(iwdev, iwcq);
error:
	kfree(iwcq);
	return ERR_PTR(err_code);
}