#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct iw_cm_id* iw; } ;
struct TYPE_3__ {scalar_t__ qp; int /*<<< orphan*/  device; } ;
struct rdma_id_private {TYPE_2__ cm_id; int /*<<< orphan*/  qp_num; TYPE_1__ id; int /*<<< orphan*/  tos_set; int /*<<< orphan*/  tos; } ;
struct rdma_conn_param {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  initiator_depth; } ;
struct iw_cm_id {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  tos_set; int /*<<< orphan*/  tos; } ;
struct iw_cm_conn_param {int /*<<< orphan*/  qpn; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iw_cm_id*) ; 
 int PTR_ERR (struct iw_cm_id*) ; 
 int /*<<< orphan*/  cma_dst_addr (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_iw_handler ; 
 int cma_modify_qp_rtr (struct rdma_id_private*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  cma_src_addr (struct rdma_id_private*) ; 
 int iw_cm_connect (struct iw_cm_id*,struct iw_cm_conn_param*) ; 
 struct iw_cm_id* iw_create_cm_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rdma_id_private*) ; 
 int /*<<< orphan*/  iw_destroy_cm_id (struct iw_cm_id*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iw_cm_conn_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_addr_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_connect_iw(struct rdma_id_private *id_priv,
			  struct rdma_conn_param *conn_param)
{
	struct iw_cm_id *cm_id;
	int ret;
	struct iw_cm_conn_param iw_param;

	cm_id = iw_create_cm_id(id_priv->id.device, cma_iw_handler, id_priv);
	if (IS_ERR(cm_id))
		return PTR_ERR(cm_id);

	cm_id->tos = id_priv->tos;
	cm_id->tos_set = id_priv->tos_set;
	id_priv->cm_id.iw = cm_id;

	memcpy(&cm_id->local_addr, cma_src_addr(id_priv),
	       rdma_addr_size(cma_src_addr(id_priv)));
	memcpy(&cm_id->remote_addr, cma_dst_addr(id_priv),
	       rdma_addr_size(cma_dst_addr(id_priv)));

	ret = cma_modify_qp_rtr(id_priv, conn_param);
	if (ret)
		goto out;

	if (conn_param) {
		iw_param.ord = conn_param->initiator_depth;
		iw_param.ird = conn_param->responder_resources;
		iw_param.private_data = conn_param->private_data;
		iw_param.private_data_len = conn_param->private_data_len;
		iw_param.qpn = id_priv->id.qp ? id_priv->qp_num : conn_param->qp_num;
	} else {
		memset(&iw_param, 0, sizeof iw_param);
		iw_param.qpn = id_priv->qp_num;
	}
	ret = iw_cm_connect(cm_id, &iw_param);
out:
	if (ret) {
		iw_destroy_cm_id(cm_id);
		id_priv->cm_id.iw = NULL;
	}
	return ret;
}