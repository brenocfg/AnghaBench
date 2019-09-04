#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_demux_pv_ctx {scalar_t__ state; int has_smi; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * pd; TYPE_3__* qp; int /*<<< orphan*/ * wq; int /*<<< orphan*/  work; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  port; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; } ;
struct TYPE_6__ {TYPE_1__* demux; } ;
struct TYPE_8__ {TYPE_2__ sriov; } ;
struct TYPE_7__ {int /*<<< orphan*/ * qp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 scalar_t__ DEMUX_PV_STATE_ACTIVE ; 
 scalar_t__ DEMUX_PV_STATE_DOWN ; 
 scalar_t__ DEMUX_PV_STATE_STARTING ; 
 int EEXIST ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_SMI ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MLX4_NUM_TUNNEL_BUFS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int create_pv_sqp (struct mlx4_ib_demux_pv_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ib_alloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_create_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx4_ib_demux_pv_ctx*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int ib_req_notify_cq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlx4_ib_alloc_pv_bufs (struct mlx4_ib_demux_pv_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_ib_free_pv_qp_bufs (struct mlx4_ib_demux_pv_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_ib_sqp_comp_worker ; 
 int /*<<< orphan*/  mlx4_ib_tunnel_comp_handler ; 
 int /*<<< orphan*/  mlx4_ib_tunnel_comp_worker ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 
 TYPE_4__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int create_pv_resources(struct ib_device *ibdev, int slave, int port,
			       int create_tun, struct mlx4_ib_demux_pv_ctx *ctx)
{
	int ret, cq_size;
	struct ib_cq_init_attr cq_attr = {};

	if (ctx->state != DEMUX_PV_STATE_DOWN)
		return -EEXIST;

	ctx->state = DEMUX_PV_STATE_STARTING;
	/* have QP0 only if link layer is IB */
	if (rdma_port_get_link_layer(ibdev, ctx->port) ==
	    IB_LINK_LAYER_INFINIBAND)
		ctx->has_smi = 1;

	if (ctx->has_smi) {
		ret = mlx4_ib_alloc_pv_bufs(ctx, IB_QPT_SMI, create_tun);
		if (ret) {
			pr_err("Failed allocating qp0 tunnel bufs (%d)\n", ret);
			goto err_out;
		}
	}

	ret = mlx4_ib_alloc_pv_bufs(ctx, IB_QPT_GSI, create_tun);
	if (ret) {
		pr_err("Failed allocating qp1 tunnel bufs (%d)\n", ret);
		goto err_out_qp0;
	}

	cq_size = 2 * MLX4_NUM_TUNNEL_BUFS;
	if (ctx->has_smi)
		cq_size *= 2;

	cq_attr.cqe = cq_size;
	ctx->cq = ib_create_cq(ctx->ib_dev, mlx4_ib_tunnel_comp_handler,
			       NULL, ctx, &cq_attr);
	if (IS_ERR(ctx->cq)) {
		ret = PTR_ERR(ctx->cq);
		pr_err("Couldn't create tunnel CQ (%d)\n", ret);
		goto err_buf;
	}

	ctx->pd = ib_alloc_pd(ctx->ib_dev, 0);
	if (IS_ERR(ctx->pd)) {
		ret = PTR_ERR(ctx->pd);
		pr_err("Couldn't create tunnel PD (%d)\n", ret);
		goto err_cq;
	}

	if (ctx->has_smi) {
		ret = create_pv_sqp(ctx, IB_QPT_SMI, create_tun);
		if (ret) {
			pr_err("Couldn't create %s QP0 (%d)\n",
			       create_tun ? "tunnel for" : "",  ret);
			goto err_pd;
		}
	}

	ret = create_pv_sqp(ctx, IB_QPT_GSI, create_tun);
	if (ret) {
		pr_err("Couldn't create %s QP1 (%d)\n",
		       create_tun ? "tunnel for" : "",  ret);
		goto err_qp0;
	}

	if (create_tun)
		INIT_WORK(&ctx->work, mlx4_ib_tunnel_comp_worker);
	else
		INIT_WORK(&ctx->work, mlx4_ib_sqp_comp_worker);

	ctx->wq = to_mdev(ibdev)->sriov.demux[port - 1].wq;

	ret = ib_req_notify_cq(ctx->cq, IB_CQ_NEXT_COMP);
	if (ret) {
		pr_err("Couldn't arm tunnel cq (%d)\n", ret);
		goto err_wq;
	}
	ctx->state = DEMUX_PV_STATE_ACTIVE;
	return 0;

err_wq:
	ctx->wq = NULL;
	ib_destroy_qp(ctx->qp[1].qp);
	ctx->qp[1].qp = NULL;


err_qp0:
	if (ctx->has_smi)
		ib_destroy_qp(ctx->qp[0].qp);
	ctx->qp[0].qp = NULL;

err_pd:
	ib_dealloc_pd(ctx->pd);
	ctx->pd = NULL;

err_cq:
	ib_destroy_cq(ctx->cq);
	ctx->cq = NULL;

err_buf:
	mlx4_ib_free_pv_qp_bufs(ctx, IB_QPT_GSI, create_tun);

err_out_qp0:
	if (ctx->has_smi)
		mlx4_ib_free_pv_qp_bufs(ctx, IB_QPT_SMI, create_tun);
err_out:
	ctx->state = DEMUX_PV_STATE_DOWN;
	return ret;
}