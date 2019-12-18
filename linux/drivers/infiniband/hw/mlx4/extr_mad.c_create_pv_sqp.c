#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_send_wr; int max_recv_wr; int max_send_sge; int max_recv_sge; } ;
struct TYPE_9__ {int qp_type; int port_num; int /*<<< orphan*/  event_handler; struct mlx4_ib_demux_pv_ctx* qp_context; int /*<<< orphan*/  create_flags; TYPE_1__ cap; int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct mlx4_ib_qp_tunnel_init_attr {int port; size_t slave; int proxy_qp_type; int port_num; scalar_t__ sq_psn; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey_index; TYPE_4__ init_attr; } ;
struct mlx4_ib_demux_pv_qp {int /*<<< orphan*/ * qp; } ;
struct mlx4_ib_demux_pv_ctx {int port; size_t slave; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  pd; int /*<<< orphan*/  cq; struct mlx4_ib_demux_pv_qp* qp; } ;
struct ib_qp_attr {int port; size_t slave; int proxy_qp_type; int port_num; scalar_t__ sq_psn; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey_index; TYPE_4__ init_attr; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_7__ {int /*<<< orphan*/ *** virt2phys_pkey; } ;
struct TYPE_8__ {TYPE_2__ pkeys; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_DEFAULT_PKEY_FULL ; 
 int /*<<< orphan*/  IB_QP1_QKEY ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int /*<<< orphan*/  IB_QPS_RTS ; 
 int IB_QPT_GSI ; 
 int IB_QPT_UD ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_QKEY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_IB_SRIOV_SQP ; 
 int /*<<< orphan*/  MLX4_IB_SRIOV_TUNNEL_QP ; 
 int MLX4_NUM_TUNNEL_BUFS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int find_slave_port_pkey_ix (TYPE_3__*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ib_create_qp (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int ib_modify_qp (int /*<<< orphan*/ *,struct mlx4_ib_qp_tunnel_init_attr*,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_ib_qp_tunnel_init_attr*,int /*<<< orphan*/ ,int) ; 
 int mlx4_ib_post_pv_qp_buf (struct mlx4_ib_demux_pv_ctx*,struct mlx4_ib_demux_pv_qp*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pv_qp_event_handler ; 
 TYPE_3__* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_pv_sqp(struct mlx4_ib_demux_pv_ctx *ctx,
			    enum ib_qp_type qp_type, int create_tun)
{
	int i, ret;
	struct mlx4_ib_demux_pv_qp *tun_qp;
	struct mlx4_ib_qp_tunnel_init_attr qp_init_attr;
	struct ib_qp_attr attr;
	int qp_attr_mask_INIT;

	if (qp_type > IB_QPT_GSI)
		return -EINVAL;

	tun_qp = &ctx->qp[qp_type];

	memset(&qp_init_attr, 0, sizeof qp_init_attr);
	qp_init_attr.init_attr.send_cq = ctx->cq;
	qp_init_attr.init_attr.recv_cq = ctx->cq;
	qp_init_attr.init_attr.sq_sig_type = IB_SIGNAL_ALL_WR;
	qp_init_attr.init_attr.cap.max_send_wr = MLX4_NUM_TUNNEL_BUFS;
	qp_init_attr.init_attr.cap.max_recv_wr = MLX4_NUM_TUNNEL_BUFS;
	qp_init_attr.init_attr.cap.max_send_sge = 1;
	qp_init_attr.init_attr.cap.max_recv_sge = 1;
	if (create_tun) {
		qp_init_attr.init_attr.qp_type = IB_QPT_UD;
		qp_init_attr.init_attr.create_flags = MLX4_IB_SRIOV_TUNNEL_QP;
		qp_init_attr.port = ctx->port;
		qp_init_attr.slave = ctx->slave;
		qp_init_attr.proxy_qp_type = qp_type;
		qp_attr_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX |
			   IB_QP_QKEY | IB_QP_PORT;
	} else {
		qp_init_attr.init_attr.qp_type = qp_type;
		qp_init_attr.init_attr.create_flags = MLX4_IB_SRIOV_SQP;
		qp_attr_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_QKEY;
	}
	qp_init_attr.init_attr.port_num = ctx->port;
	qp_init_attr.init_attr.qp_context = ctx;
	qp_init_attr.init_attr.event_handler = pv_qp_event_handler;
	tun_qp->qp = ib_create_qp(ctx->pd, &qp_init_attr.init_attr);
	if (IS_ERR(tun_qp->qp)) {
		ret = PTR_ERR(tun_qp->qp);
		tun_qp->qp = NULL;
		pr_err("Couldn't create %s QP (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		return ret;
	}

	memset(&attr, 0, sizeof attr);
	attr.qp_state = IB_QPS_INIT;
	ret = 0;
	if (create_tun)
		ret = find_slave_port_pkey_ix(to_mdev(ctx->ib_dev), ctx->slave,
					      ctx->port, IB_DEFAULT_PKEY_FULL,
					      &attr.pkey_index);
	if (ret || !create_tun)
		attr.pkey_index =
			to_mdev(ctx->ib_dev)->pkeys.virt2phys_pkey[ctx->slave][ctx->port - 1][0];
	attr.qkey = IB_QP1_QKEY;
	attr.port_num = ctx->port;
	ret = ib_modify_qp(tun_qp->qp, &attr, qp_attr_mask_INIT);
	if (ret) {
		pr_err("Couldn't change %s qp state to INIT (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		goto err_qp;
	}
	attr.qp_state = IB_QPS_RTR;
	ret = ib_modify_qp(tun_qp->qp, &attr, IB_QP_STATE);
	if (ret) {
		pr_err("Couldn't change %s qp state to RTR (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		goto err_qp;
	}
	attr.qp_state = IB_QPS_RTS;
	attr.sq_psn = 0;
	ret = ib_modify_qp(tun_qp->qp, &attr, IB_QP_STATE | IB_QP_SQ_PSN);
	if (ret) {
		pr_err("Couldn't change %s qp state to RTS (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		goto err_qp;
	}

	for (i = 0; i < MLX4_NUM_TUNNEL_BUFS; i++) {
		ret = mlx4_ib_post_pv_qp_buf(ctx, tun_qp, i);
		if (ret) {
			pr_err(" mlx4_ib_post_pv_buf error"
			       " (err = %d, i = %d)\n", ret, i);
			goto err_qp;
		}
	}
	return 0;

err_qp:
	ib_destroy_qp(tun_qp->qp);
	tun_qp->qp = NULL;
	return ret;
}