#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uresp ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct ib_udata {int dummy; } ;
struct TYPE_22__ {scalar_t__ max_inline_data; scalar_t__ max_send_sge; scalar_t__ max_recv_sge; int max_send_wr; int max_recv_wr; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; scalar_t__ sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; TYPE_1__ cap; scalar_t__ create_flags; } ;
struct ib_qp {size_t qp_num; } ;
struct ib_pd {TYPE_14__* uobject; int /*<<< orphan*/  device; } ;
struct i40iwarp_offload_info {int rd_enable; int wr_rdresp_en; int fast_reg_en; int priv_mode_en; int ddp_ver; int rdmap_ver; } ;
struct i40iw_ucontext {int /*<<< orphan*/  qp_reg_mem_list_lock; int /*<<< orphan*/  qp_reg_mem_list; } ;
struct i40iw_sc_qp {scalar_t__ push_idx; void* back_qp; } ;
struct i40iw_sc_dev {TYPE_9__* iw_priv_qp_ops; int /*<<< orphan*/  hw; } ;
struct TYPE_23__ {int sq_size; int rq_size; scalar_t__ max_sq_frag_cnt; scalar_t__ max_rq_frag_cnt; scalar_t__ max_inline_data; size_t qp_id; } ;
struct i40iw_qp_init_info {int q2_pa; int host_ctx_pa; int cq_num_valid; int actual_sq_size; int actual_rq_size; size_t qp_id; scalar_t__ push_idx; int /*<<< orphan*/  next_iwarp_state; int /*<<< orphan*/  type; TYPE_2__ qp_uk_init_info; int /*<<< orphan*/ * pd; void* host_ctx; scalar_t__ q2; int /*<<< orphan*/ * vsi; } ;
struct i40iw_qp_host_ctx_info {uintptr_t qp_compl_ctx; int iwarp_info_valid; int push_mode_en; scalar_t__ push_idx; int /*<<< orphan*/  rcv_cq_num; int /*<<< orphan*/  send_cq_num; struct i40iwarp_offload_info* iwarp_info; } ;
struct TYPE_16__ {int pa; int size; void* va; } ;
struct TYPE_21__ {int pa; scalar_t__ va; } ;
struct i40iw_qp {int user_mode; int sig_all; struct ib_qp ibqp; int /*<<< orphan*/  rq_drained; int /*<<< orphan*/  sq_drained; struct i40iw_pd* iwpd; int /*<<< orphan*/  lock; TYPE_10__ host_ctx; struct i40iw_sc_qp sc_qp; TYPE_8__* iwrcq; TYPE_5__* iwscq; struct i40iwarp_offload_info iwarp_info; struct i40iw_qp_host_ctx_info ctx_info; int /*<<< orphan*/  iwpbl; struct i40iw_device* iwdev; TYPE_15__ q2_ctx_mem; void* allocated_buffer; } ;
struct i40iw_pd {int /*<<< orphan*/  sc_pd; } ;
struct i40iw_pbl {int dummy; } ;
struct i40iw_cqp {int dummy; } ;
struct i40iw_device {struct i40iw_qp** qp_table; scalar_t__ push_mode; int /*<<< orphan*/  next_qp; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  allocated_qps; int /*<<< orphan*/  vsi; scalar_t__ closing; struct i40iw_sc_dev sc_dev; struct i40iw_cqp cqp; } ;
struct i40iw_create_qp_resp {int q2_pa; int host_ctx_pa; int cq_num_valid; int actual_sq_size; int actual_rq_size; size_t qp_id; scalar_t__ push_idx; int /*<<< orphan*/  next_iwarp_state; int /*<<< orphan*/  type; TYPE_2__ qp_uk_init_info; int /*<<< orphan*/ * pd; void* host_ctx; scalar_t__ q2; int /*<<< orphan*/ * vsi; } ;
struct i40iw_create_qp_req {uintptr_t user_compl_ctx; scalar_t__ user_wqe_buffers; } ;
struct i40iw_create_qp_info {int q2_pa; int host_ctx_pa; int cq_num_valid; int actual_sq_size; int actual_rq_size; size_t qp_id; scalar_t__ push_idx; int /*<<< orphan*/  next_iwarp_state; int /*<<< orphan*/  type; TYPE_2__ qp_uk_init_info; int /*<<< orphan*/ * pd; void* host_ctx; scalar_t__ q2; int /*<<< orphan*/ * vsi; } ;
struct TYPE_17__ {uintptr_t scratch; struct i40iw_sc_qp* qp; struct i40iw_qp_init_info info; } ;
struct TYPE_18__ {TYPE_11__ qp_create; } ;
struct TYPE_19__ {TYPE_12__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_13__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  init_info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_30__ {int (* qp_init ) (struct i40iw_sc_qp*,struct i40iw_qp_init_info*) ;int (* qp_setctx ) (struct i40iw_sc_qp*,int /*<<< orphan*/ *,struct i40iw_qp_host_ctx_info*) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  cq_id; } ;
struct TYPE_28__ {TYPE_6__ cq_uk; } ;
struct TYPE_29__ {TYPE_7__ sc_cq; } ;
struct TYPE_24__ {int /*<<< orphan*/  cq_id; } ;
struct TYPE_25__ {TYPE_3__ cq_uk; } ;
struct TYPE_26__ {TYPE_4__ sc_cq; } ;
struct TYPE_20__ {scalar_t__ context; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROTO ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I40IW_INVALID_PUSH_PAGE_INDEX ; 
 scalar_t__ I40IW_MAX_INLINE_DATA_SIZE ; 
 scalar_t__ I40IW_MAX_WQ_FRAGMENT_COUNT ; 
 int I40IW_Q2_BUFFER_SIZE ; 
 int I40IW_QP_CTX_SIZE ; 
 int /*<<< orphan*/  I40IW_QP_STATE_IDLE ; 
 int /*<<< orphan*/  I40IW_QP_TYPE_IWARP ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  OP_QP_CREATE ; 
 int /*<<< orphan*/  i40iw_add_devusecount (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_add_pdusecount (struct i40iw_pd*) ; 
 int /*<<< orphan*/  i40iw_add_ref (struct ib_qp*) ; 
 int /*<<< orphan*/  i40iw_alloc_push_page (struct i40iw_device*,struct i40iw_sc_qp*) ; 
 int i40iw_alloc_resource (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40iw_allocate_dma_mem (int /*<<< orphan*/ ,TYPE_15__*,int,int) ; 
 int /*<<< orphan*/  i40iw_destroy_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  i40iw_free_qp_resources (struct i40iw_device*,struct i40iw_qp*,size_t) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (struct i40iw_cqp*,int) ; 
 struct i40iw_pbl* i40iw_get_pbl (unsigned long,int /*<<< orphan*/ *) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int i40iw_setup_kmode_qp (struct i40iw_device*,struct i40iw_qp*,struct i40iw_qp_init_info*) ; 
 int i40iw_setup_virt_qp (struct i40iw_device*,struct i40iw_qp*,struct i40iw_qp_init_info*) ; 
 int ib_copy_from_udata (struct i40iw_create_qp_req*,struct ib_udata*,int) ; 
 int ib_copy_to_udata (struct ib_udata*,struct i40iw_qp_init_info*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct i40iw_pbl*,int) ; 
 int /*<<< orphan*/  memset (struct i40iw_qp_init_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct i40iw_sc_qp*,struct i40iw_qp_init_info*) ; 
 int stub2 (struct i40iw_sc_qp*,int /*<<< orphan*/ *,struct i40iw_qp_host_ctx_info*) ; 
 void* to_iwcq (int /*<<< orphan*/ ) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 
 struct i40iw_pd* to_iwpd (struct ib_pd*) ; 
 struct i40iw_ucontext* to_ucontext (scalar_t__) ; 

__attribute__((used)) static struct ib_qp *i40iw_create_qp(struct ib_pd *ibpd,
				     struct ib_qp_init_attr *init_attr,
				     struct ib_udata *udata)
{
	struct i40iw_pd *iwpd = to_iwpd(ibpd);
	struct i40iw_device *iwdev = to_iwdev(ibpd->device);
	struct i40iw_cqp *iwcqp = &iwdev->cqp;
	struct i40iw_qp *iwqp;
	struct i40iw_ucontext *ucontext;
	struct i40iw_create_qp_req req;
	struct i40iw_create_qp_resp uresp;
	u32 qp_num = 0;
	void *mem;
	enum i40iw_status_code ret;
	int err_code;
	int sq_size;
	int rq_size;
	struct i40iw_sc_qp *qp;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_qp_init_info init_info;
	struct i40iw_create_qp_info *qp_info;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;

	struct i40iw_qp_host_ctx_info *ctx_info;
	struct i40iwarp_offload_info *iwarp_info;
	unsigned long flags;

	if (iwdev->closing)
		return ERR_PTR(-ENODEV);

	if (init_attr->create_flags)
		return ERR_PTR(-EINVAL);
	if (init_attr->cap.max_inline_data > I40IW_MAX_INLINE_DATA_SIZE)
		init_attr->cap.max_inline_data = I40IW_MAX_INLINE_DATA_SIZE;

	if (init_attr->cap.max_send_sge > I40IW_MAX_WQ_FRAGMENT_COUNT)
		init_attr->cap.max_send_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;

	if (init_attr->cap.max_recv_sge > I40IW_MAX_WQ_FRAGMENT_COUNT)
		init_attr->cap.max_recv_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;

	memset(&init_info, 0, sizeof(init_info));

	sq_size = init_attr->cap.max_send_wr;
	rq_size = init_attr->cap.max_recv_wr;

	init_info.vsi = &iwdev->vsi;
	init_info.qp_uk_init_info.sq_size = sq_size;
	init_info.qp_uk_init_info.rq_size = rq_size;
	init_info.qp_uk_init_info.max_sq_frag_cnt = init_attr->cap.max_send_sge;
	init_info.qp_uk_init_info.max_rq_frag_cnt = init_attr->cap.max_recv_sge;
	init_info.qp_uk_init_info.max_inline_data = init_attr->cap.max_inline_data;

	mem = kzalloc(sizeof(*iwqp), GFP_KERNEL);
	if (!mem)
		return ERR_PTR(-ENOMEM);

	iwqp = (struct i40iw_qp *)mem;
	iwqp->allocated_buffer = mem;
	qp = &iwqp->sc_qp;
	qp->back_qp = (void *)iwqp;
	qp->push_idx = I40IW_INVALID_PUSH_PAGE_INDEX;

	iwqp->ctx_info.iwarp_info = &iwqp->iwarp_info;

	if (i40iw_allocate_dma_mem(dev->hw,
				   &iwqp->q2_ctx_mem,
				   I40IW_Q2_BUFFER_SIZE + I40IW_QP_CTX_SIZE,
				   256)) {
		i40iw_pr_err("dma_mem failed\n");
		err_code = -ENOMEM;
		goto error;
	}

	init_info.q2 = iwqp->q2_ctx_mem.va;
	init_info.q2_pa = iwqp->q2_ctx_mem.pa;

	init_info.host_ctx = (void *)init_info.q2 + I40IW_Q2_BUFFER_SIZE;
	init_info.host_ctx_pa = init_info.q2_pa + I40IW_Q2_BUFFER_SIZE;

	err_code = i40iw_alloc_resource(iwdev, iwdev->allocated_qps, iwdev->max_qp,
					&qp_num, &iwdev->next_qp);
	if (err_code) {
		i40iw_pr_err("qp resource\n");
		goto error;
	}

	iwqp->iwdev = iwdev;
	iwqp->iwpd = iwpd;
	iwqp->ibqp.qp_num = qp_num;
	qp = &iwqp->sc_qp;
	iwqp->iwscq = to_iwcq(init_attr->send_cq);
	iwqp->iwrcq = to_iwcq(init_attr->recv_cq);

	iwqp->host_ctx.va = init_info.host_ctx;
	iwqp->host_ctx.pa = init_info.host_ctx_pa;
	iwqp->host_ctx.size = I40IW_QP_CTX_SIZE;

	init_info.pd = &iwpd->sc_pd;
	init_info.qp_uk_init_info.qp_id = iwqp->ibqp.qp_num;
	iwqp->ctx_info.qp_compl_ctx = (uintptr_t)qp;

	if (init_attr->qp_type != IB_QPT_RC) {
		err_code = -EINVAL;
		goto error;
	}
	if (iwdev->push_mode)
		i40iw_alloc_push_page(iwdev, qp);
	if (udata) {
		err_code = ib_copy_from_udata(&req, udata, sizeof(req));
		if (err_code) {
			i40iw_pr_err("ib_copy_from_data\n");
			goto error;
		}
		iwqp->ctx_info.qp_compl_ctx = req.user_compl_ctx;
		if (ibpd->uobject && ibpd->uobject->context) {
			iwqp->user_mode = 1;
			ucontext = to_ucontext(ibpd->uobject->context);

			if (req.user_wqe_buffers) {
				struct i40iw_pbl *iwpbl;

				spin_lock_irqsave(
				    &ucontext->qp_reg_mem_list_lock, flags);
				iwpbl = i40iw_get_pbl(
				    (unsigned long)req.user_wqe_buffers,
				    &ucontext->qp_reg_mem_list);
				spin_unlock_irqrestore(
				    &ucontext->qp_reg_mem_list_lock, flags);

				if (!iwpbl) {
					err_code = -ENODATA;
					i40iw_pr_err("no pbl info\n");
					goto error;
				}
				memcpy(&iwqp->iwpbl, iwpbl, sizeof(iwqp->iwpbl));
			}
		}
		err_code = i40iw_setup_virt_qp(iwdev, iwqp, &init_info);
	} else {
		err_code = i40iw_setup_kmode_qp(iwdev, iwqp, &init_info);
	}

	if (err_code) {
		i40iw_pr_err("setup qp failed\n");
		goto error;
	}

	init_info.type = I40IW_QP_TYPE_IWARP;
	ret = dev->iw_priv_qp_ops->qp_init(qp, &init_info);
	if (ret) {
		err_code = -EPROTO;
		i40iw_pr_err("qp_init fail\n");
		goto error;
	}
	ctx_info = &iwqp->ctx_info;
	iwarp_info = &iwqp->iwarp_info;
	iwarp_info->rd_enable = true;
	iwarp_info->wr_rdresp_en = true;
	if (!iwqp->user_mode) {
		iwarp_info->fast_reg_en = true;
		iwarp_info->priv_mode_en = true;
	}
	iwarp_info->ddp_ver = 1;
	iwarp_info->rdmap_ver = 1;

	ctx_info->iwarp_info_valid = true;
	ctx_info->send_cq_num = iwqp->iwscq->sc_cq.cq_uk.cq_id;
	ctx_info->rcv_cq_num = iwqp->iwrcq->sc_cq.cq_uk.cq_id;
	if (qp->push_idx == I40IW_INVALID_PUSH_PAGE_INDEX) {
		ctx_info->push_mode_en = false;
	} else {
		ctx_info->push_mode_en = true;
		ctx_info->push_idx = qp->push_idx;
	}

	ret = dev->iw_priv_qp_ops->qp_setctx(&iwqp->sc_qp,
					     (u64 *)iwqp->host_ctx.va,
					     ctx_info);
	ctx_info->iwarp_info_valid = false;
	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	if (!cqp_request) {
		err_code = -ENOMEM;
		goto error;
	}
	cqp_info = &cqp_request->info;
	qp_info = &cqp_request->info.in.u.qp_create.info;

	memset(qp_info, 0, sizeof(*qp_info));

	qp_info->cq_num_valid = true;
	qp_info->next_iwarp_state = I40IW_QP_STATE_IDLE;

	cqp_info->cqp_cmd = OP_QP_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_create.qp = qp;
	cqp_info->in.u.qp_create.scratch = (uintptr_t)cqp_request;
	ret = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (ret) {
		i40iw_pr_err("CQP-OP QP create fail");
		err_code = -EACCES;
		goto error;
	}

	i40iw_add_ref(&iwqp->ibqp);
	spin_lock_init(&iwqp->lock);
	iwqp->sig_all = (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR) ? 1 : 0;
	iwdev->qp_table[qp_num] = iwqp;
	i40iw_add_pdusecount(iwqp->iwpd);
	i40iw_add_devusecount(iwdev);
	if (ibpd->uobject && udata) {
		memset(&uresp, 0, sizeof(uresp));
		uresp.actual_sq_size = sq_size;
		uresp.actual_rq_size = rq_size;
		uresp.qp_id = qp_num;
		uresp.push_idx = qp->push_idx;
		err_code = ib_copy_to_udata(udata, &uresp, sizeof(uresp));
		if (err_code) {
			i40iw_pr_err("copy_to_udata failed\n");
			i40iw_destroy_qp(&iwqp->ibqp);
			   /* let the completion of the qp destroy free the qp */
			return ERR_PTR(err_code);
		}
	}
	init_completion(&iwqp->sq_drained);
	init_completion(&iwqp->rq_drained);

	return &iwqp->ibqp;
error:
	i40iw_free_qp_resources(iwdev, iwqp, qp_num);
	return ERR_PTR(err_code);
}