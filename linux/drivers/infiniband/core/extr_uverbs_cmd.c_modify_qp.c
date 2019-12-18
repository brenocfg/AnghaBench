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
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct TYPE_6__ {scalar_t__ port_num; } ;
struct TYPE_5__ {int attr_mask; scalar_t__ port_num; scalar_t__ qp_state; scalar_t__ alt_port_num; scalar_t__ cur_qp_state; TYPE_3__ alt_dest; TYPE_3__ dest; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  qp_handle; } ;
struct ib_uverbs_ex_modify_qp {TYPE_2__ base; int /*<<< orphan*/  rate_limit; } ;
struct ib_qp_attr {scalar_t__ qp_state; scalar_t__ cur_qp_state; scalar_t__ port_num; scalar_t__ alt_port_num; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  rate_limit; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; } ;
struct ib_qp {int /*<<< orphan*/  qp_type; int /*<<< orphan*/  device; TYPE_1__* real_qp; } ;
struct TYPE_4__ {scalar_t__ port; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_RTR ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_AV ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_EN_SQD_ASYNC_NOTIFY ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_PATH_MIG_STATE ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_QKEY ; 
 int IB_QP_RATE_LIMIT ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_RQ_PSN ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int IB_QP_TIMEOUT ; 
 int /*<<< orphan*/  UVERBS_OBJECT_QP ; 
 int /*<<< orphan*/  copy_ah_attr_from_uverbs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ib_modify_qp_with_udata (struct ib_qp*,struct ib_qp_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_qp_attr*) ; 
 struct ib_qp_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_qp_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_is_port_valid (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ib_qp* uobj_get_obj_read (struct ib_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_qp*) ; 

__attribute__((used)) static int modify_qp(struct uverbs_attr_bundle *attrs,
		     struct ib_uverbs_ex_modify_qp *cmd)
{
	struct ib_qp_attr *attr;
	struct ib_qp *qp;
	int ret;

	attr = kzalloc(sizeof(*attr), GFP_KERNEL);
	if (!attr)
		return -ENOMEM;

	qp = uobj_get_obj_read(qp, UVERBS_OBJECT_QP, cmd->base.qp_handle,
			       attrs);
	if (!qp) {
		ret = -EINVAL;
		goto out;
	}

	if ((cmd->base.attr_mask & IB_QP_PORT) &&
	    !rdma_is_port_valid(qp->device, cmd->base.port_num)) {
		ret = -EINVAL;
		goto release_qp;
	}

	if ((cmd->base.attr_mask & IB_QP_AV)) {
		if (!rdma_is_port_valid(qp->device, cmd->base.dest.port_num)) {
			ret = -EINVAL;
			goto release_qp;
		}

		if (cmd->base.attr_mask & IB_QP_STATE &&
		    cmd->base.qp_state == IB_QPS_RTR) {
		/* We are in INIT->RTR TRANSITION (if we are not,
		 * this transition will be rejected in subsequent checks).
		 * In the INIT->RTR transition, we cannot have IB_QP_PORT set,
		 * but the IB_QP_STATE flag is required.
		 *
		 * Since kernel 3.14 (commit dbf727de7440), the uverbs driver,
		 * when IB_QP_AV is set, has required inclusion of a valid
		 * port number in the primary AV. (AVs are created and handled
		 * differently for infiniband and ethernet (RoCE) ports).
		 *
		 * Check the port number included in the primary AV against
		 * the port number in the qp struct, which was set (and saved)
		 * in the RST->INIT transition.
		 */
			if (cmd->base.dest.port_num != qp->real_qp->port) {
				ret = -EINVAL;
				goto release_qp;
			}
		} else {
		/* We are in SQD->SQD. (If we are not, this transition will
		 * be rejected later in the verbs layer checks).
		 * Check for both IB_QP_PORT and IB_QP_AV, these can be set
		 * together in the SQD->SQD transition.
		 *
		 * If only IP_QP_AV was set, add in IB_QP_PORT as well (the
		 * verbs layer driver does not track primary port changes
		 * resulting from path migration. Thus, in SQD, if the primary
		 * AV is modified, the primary port should also be modified).
		 *
		 * Note that in this transition, the IB_QP_STATE flag
		 * is not allowed.
		 */
			if (((cmd->base.attr_mask & (IB_QP_AV | IB_QP_PORT))
			     == (IB_QP_AV | IB_QP_PORT)) &&
			    cmd->base.port_num != cmd->base.dest.port_num) {
				ret = -EINVAL;
				goto release_qp;
			}
			if ((cmd->base.attr_mask & (IB_QP_AV | IB_QP_PORT))
			    == IB_QP_AV) {
				cmd->base.attr_mask |= IB_QP_PORT;
				cmd->base.port_num = cmd->base.dest.port_num;
			}
		}
	}

	if ((cmd->base.attr_mask & IB_QP_ALT_PATH) &&
	    (!rdma_is_port_valid(qp->device, cmd->base.alt_port_num) ||
	    !rdma_is_port_valid(qp->device, cmd->base.alt_dest.port_num) ||
	    cmd->base.alt_port_num != cmd->base.alt_dest.port_num)) {
		ret = -EINVAL;
		goto release_qp;
	}

	if ((cmd->base.attr_mask & IB_QP_CUR_STATE &&
	    cmd->base.cur_qp_state > IB_QPS_ERR) ||
	    (cmd->base.attr_mask & IB_QP_STATE &&
	    cmd->base.qp_state > IB_QPS_ERR)) {
		ret = -EINVAL;
		goto release_qp;
	}

	if (cmd->base.attr_mask & IB_QP_STATE)
		attr->qp_state = cmd->base.qp_state;
	if (cmd->base.attr_mask & IB_QP_CUR_STATE)
		attr->cur_qp_state = cmd->base.cur_qp_state;
	if (cmd->base.attr_mask & IB_QP_PATH_MTU)
		attr->path_mtu = cmd->base.path_mtu;
	if (cmd->base.attr_mask & IB_QP_PATH_MIG_STATE)
		attr->path_mig_state = cmd->base.path_mig_state;
	if (cmd->base.attr_mask & IB_QP_QKEY)
		attr->qkey = cmd->base.qkey;
	if (cmd->base.attr_mask & IB_QP_RQ_PSN)
		attr->rq_psn = cmd->base.rq_psn;
	if (cmd->base.attr_mask & IB_QP_SQ_PSN)
		attr->sq_psn = cmd->base.sq_psn;
	if (cmd->base.attr_mask & IB_QP_DEST_QPN)
		attr->dest_qp_num = cmd->base.dest_qp_num;
	if (cmd->base.attr_mask & IB_QP_ACCESS_FLAGS)
		attr->qp_access_flags = cmd->base.qp_access_flags;
	if (cmd->base.attr_mask & IB_QP_PKEY_INDEX)
		attr->pkey_index = cmd->base.pkey_index;
	if (cmd->base.attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY)
		attr->en_sqd_async_notify = cmd->base.en_sqd_async_notify;
	if (cmd->base.attr_mask & IB_QP_MAX_QP_RD_ATOMIC)
		attr->max_rd_atomic = cmd->base.max_rd_atomic;
	if (cmd->base.attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		attr->max_dest_rd_atomic = cmd->base.max_dest_rd_atomic;
	if (cmd->base.attr_mask & IB_QP_MIN_RNR_TIMER)
		attr->min_rnr_timer = cmd->base.min_rnr_timer;
	if (cmd->base.attr_mask & IB_QP_PORT)
		attr->port_num = cmd->base.port_num;
	if (cmd->base.attr_mask & IB_QP_TIMEOUT)
		attr->timeout = cmd->base.timeout;
	if (cmd->base.attr_mask & IB_QP_RETRY_CNT)
		attr->retry_cnt = cmd->base.retry_cnt;
	if (cmd->base.attr_mask & IB_QP_RNR_RETRY)
		attr->rnr_retry = cmd->base.rnr_retry;
	if (cmd->base.attr_mask & IB_QP_ALT_PATH) {
		attr->alt_port_num = cmd->base.alt_port_num;
		attr->alt_timeout = cmd->base.alt_timeout;
		attr->alt_pkey_index = cmd->base.alt_pkey_index;
	}
	if (cmd->base.attr_mask & IB_QP_RATE_LIMIT)
		attr->rate_limit = cmd->rate_limit;

	if (cmd->base.attr_mask & IB_QP_AV)
		copy_ah_attr_from_uverbs(qp->device, &attr->ah_attr,
					 &cmd->base.dest);

	if (cmd->base.attr_mask & IB_QP_ALT_PATH)
		copy_ah_attr_from_uverbs(qp->device, &attr->alt_ah_attr,
					 &cmd->base.alt_dest);

	ret = ib_modify_qp_with_udata(qp, attr,
				      modify_qp_mask(qp->qp_type,
						     cmd->base.attr_mask),
				      &attrs->driver_udata);

release_qp:
	uobj_put_obj_read(qp);
out:
	kfree(attr);

	return ret;
}