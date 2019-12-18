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
struct ib_uverbs_qp_attr {int /*<<< orphan*/  reserved; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_attr {int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; TYPE_1__ cap; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_copy_ah_attr_to_user (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ib_copy_qp_attr_to_user(struct ib_device *device,
			     struct ib_uverbs_qp_attr *dst,
			     struct ib_qp_attr *src)
{
	dst->qp_state	        = src->qp_state;
	dst->cur_qp_state	= src->cur_qp_state;
	dst->path_mtu		= src->path_mtu;
	dst->path_mig_state	= src->path_mig_state;
	dst->qkey		= src->qkey;
	dst->rq_psn		= src->rq_psn;
	dst->sq_psn		= src->sq_psn;
	dst->dest_qp_num	= src->dest_qp_num;
	dst->qp_access_flags	= src->qp_access_flags;

	dst->max_send_wr	= src->cap.max_send_wr;
	dst->max_recv_wr	= src->cap.max_recv_wr;
	dst->max_send_sge	= src->cap.max_send_sge;
	dst->max_recv_sge	= src->cap.max_recv_sge;
	dst->max_inline_data	= src->cap.max_inline_data;

	ib_copy_ah_attr_to_user(device, &dst->ah_attr, &src->ah_attr);
	ib_copy_ah_attr_to_user(device, &dst->alt_ah_attr, &src->alt_ah_attr);

	dst->pkey_index		= src->pkey_index;
	dst->alt_pkey_index	= src->alt_pkey_index;
	dst->en_sqd_async_notify = src->en_sqd_async_notify;
	dst->sq_draining	= src->sq_draining;
	dst->max_rd_atomic	= src->max_rd_atomic;
	dst->max_dest_rd_atomic	= src->max_dest_rd_atomic;
	dst->min_rnr_timer	= src->min_rnr_timer;
	dst->port_num		= src->port_num;
	dst->timeout		= src->timeout;
	dst->retry_cnt		= src->retry_cnt;
	dst->rnr_retry		= src->rnr_retry;
	dst->alt_port_num	= src->alt_port_num;
	dst->alt_timeout	= src->alt_timeout;
	memset(dst->reserved, 0, sizeof(dst->reserved));
}