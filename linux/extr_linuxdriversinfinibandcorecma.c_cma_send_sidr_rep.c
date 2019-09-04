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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ib; } ;
struct rdma_id_private {TYPE_1__ cm_id; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; } ;
struct ib_cm_sidr_rep_param {int status; int private_data_len; void const* private_data; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; } ;
typedef  enum ib_cm_sidr_status { ____Placeholder_ib_cm_sidr_status } ib_cm_sidr_status ;

/* Variables and functions */
 int IB_SIDR_SUCCESS ; 
 int cma_set_qkey (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int ib_send_cm_sidr_rep (int /*<<< orphan*/ ,struct ib_cm_sidr_rep_param*) ; 
 int /*<<< orphan*/  memset (struct ib_cm_sidr_rep_param*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cma_send_sidr_rep(struct rdma_id_private *id_priv,
			     enum ib_cm_sidr_status status, u32 qkey,
			     const void *private_data, int private_data_len)
{
	struct ib_cm_sidr_rep_param rep;
	int ret;

	memset(&rep, 0, sizeof rep);
	rep.status = status;
	if (status == IB_SIDR_SUCCESS) {
		ret = cma_set_qkey(id_priv, qkey);
		if (ret)
			return ret;
		rep.qp_num = id_priv->qp_num;
		rep.qkey = id_priv->qkey;
	}
	rep.private_data = private_data;
	rep.private_data_len = private_data_len;

	return ib_send_cm_sidr_rep(id_priv->cm_id.ib, &rep);
}