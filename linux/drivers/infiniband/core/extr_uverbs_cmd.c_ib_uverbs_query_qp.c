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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_query_qp_resp {int sq_sig_all; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  alt_dest; int /*<<< orphan*/  dest; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_uverbs_query_qp {int /*<<< orphan*/  attr_mask; int /*<<< orphan*/  qp_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {scalar_t__ sq_sig_type; TYPE_1__ cap; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_qp_attr {scalar_t__ sq_sig_type; TYPE_1__ cap; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  UVERBS_OBJECT_QP ; 
 int /*<<< orphan*/  copy_ah_attr_to_uverbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ib_query_qp (struct ib_qp*,struct ib_qp_init_attr*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  kfree (struct ib_qp_init_attr*) ; 
 struct ib_qp_init_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_query_qp_resp*,int /*<<< orphan*/ ,int) ; 
 struct ib_qp* uobj_get_obj_read (struct ib_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_qp*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_query_qp*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_query_qp_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_query_qp(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_query_qp      cmd;
	struct ib_uverbs_query_qp_resp resp;
	struct ib_qp                   *qp;
	struct ib_qp_attr              *attr;
	struct ib_qp_init_attr         *init_attr;
	int                            ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	attr      = kmalloc(sizeof *attr, GFP_KERNEL);
	init_attr = kmalloc(sizeof *init_attr, GFP_KERNEL);
	if (!attr || !init_attr) {
		ret = -ENOMEM;
		goto out;
	}

	qp = uobj_get_obj_read(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	if (!qp) {
		ret = -EINVAL;
		goto out;
	}

	ret = ib_query_qp(qp, attr, cmd.attr_mask, init_attr);

	uobj_put_obj_read(qp);

	if (ret)
		goto out;

	memset(&resp, 0, sizeof resp);

	resp.qp_state               = attr->qp_state;
	resp.cur_qp_state           = attr->cur_qp_state;
	resp.path_mtu               = attr->path_mtu;
	resp.path_mig_state         = attr->path_mig_state;
	resp.qkey                   = attr->qkey;
	resp.rq_psn                 = attr->rq_psn;
	resp.sq_psn                 = attr->sq_psn;
	resp.dest_qp_num            = attr->dest_qp_num;
	resp.qp_access_flags        = attr->qp_access_flags;
	resp.pkey_index             = attr->pkey_index;
	resp.alt_pkey_index         = attr->alt_pkey_index;
	resp.sq_draining            = attr->sq_draining;
	resp.max_rd_atomic          = attr->max_rd_atomic;
	resp.max_dest_rd_atomic     = attr->max_dest_rd_atomic;
	resp.min_rnr_timer          = attr->min_rnr_timer;
	resp.port_num               = attr->port_num;
	resp.timeout                = attr->timeout;
	resp.retry_cnt              = attr->retry_cnt;
	resp.rnr_retry              = attr->rnr_retry;
	resp.alt_port_num           = attr->alt_port_num;
	resp.alt_timeout            = attr->alt_timeout;

	copy_ah_attr_to_uverbs(&resp.dest, &attr->ah_attr);
	copy_ah_attr_to_uverbs(&resp.alt_dest, &attr->alt_ah_attr);

	resp.max_send_wr            = init_attr->cap.max_send_wr;
	resp.max_recv_wr            = init_attr->cap.max_recv_wr;
	resp.max_send_sge           = init_attr->cap.max_send_sge;
	resp.max_recv_sge           = init_attr->cap.max_recv_sge;
	resp.max_inline_data        = init_attr->cap.max_inline_data;
	resp.sq_sig_all             = init_attr->sq_sig_type == IB_SIGNAL_ALL_WR;

	ret = uverbs_response(attrs, &resp, sizeof(resp));

out:
	kfree(attr);
	kfree(init_attr);

	return ret;
}