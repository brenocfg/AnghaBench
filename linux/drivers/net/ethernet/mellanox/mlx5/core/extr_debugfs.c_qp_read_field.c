#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_qp_context {int mtu_msgmax; int rq_size_stride; int /*<<< orphan*/  log_pg_sz_remote_qpn; int /*<<< orphan*/  sq_crq_size; int /*<<< orphan*/  flags; } ;
struct mlx5_core_qp {int pid; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IB_MTU_1024 141 
#define  IB_MTU_2048 140 
#define  IB_MTU_256 139 
#define  IB_MTU_4096 138 
#define  IB_MTU_512 137 
 scalar_t__ MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
#define  QP_LOG_PG_SZ 136 
#define  QP_MTU 135 
#define  QP_N_RECV 134 
#define  QP_N_SEND 133 
#define  QP_PID 132 
#define  QP_RECV_SZ 131 
#define  QP_RQPN 130 
#define  QP_STATE 129 
#define  QP_XPORT 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_qp_query (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 scalar_t__ mlx5_qp_state_str (int) ; 
 scalar_t__ mlx5_qp_type_str (int) ; 
 int /*<<< orphan*/  qpc ; 
 int /*<<< orphan*/  query_qp_out ; 

__attribute__((used)) static u64 qp_read_field(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp,
			 int index, int *is_str)
{
	int outlen = MLX5_ST_SZ_BYTES(query_qp_out);
	struct mlx5_qp_context *ctx;
	u64 param = 0;
	u32 *out;
	int err;
	int no_sq;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_qp_query(dev, qp, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query qp err=%d\n", err);
		goto out;
	}

	*is_str = 0;

	/* FIXME: use MLX5_GET rather than mlx5_qp_context manual struct */
	ctx = (struct mlx5_qp_context *)MLX5_ADDR_OF(query_qp_out, out, qpc);

	switch (index) {
	case QP_PID:
		param = qp->pid;
		break;
	case QP_STATE:
		param = (unsigned long)mlx5_qp_state_str(be32_to_cpu(ctx->flags) >> 28);
		*is_str = 1;
		break;
	case QP_XPORT:
		param = (unsigned long)mlx5_qp_type_str((be32_to_cpu(ctx->flags) >> 16) & 0xff);
		*is_str = 1;
		break;
	case QP_MTU:
		switch (ctx->mtu_msgmax >> 5) {
		case IB_MTU_256:
			param = 256;
			break;
		case IB_MTU_512:
			param = 512;
			break;
		case IB_MTU_1024:
			param = 1024;
			break;
		case IB_MTU_2048:
			param = 2048;
			break;
		case IB_MTU_4096:
			param = 4096;
			break;
		default:
			param = 0;
		}
		break;
	case QP_N_RECV:
		param = 1 << ((ctx->rq_size_stride >> 3) & 0xf);
		break;
	case QP_RECV_SZ:
		param = 1 << ((ctx->rq_size_stride & 7) + 4);
		break;
	case QP_N_SEND:
		no_sq = be16_to_cpu(ctx->sq_crq_size) >> 15;
		if (!no_sq)
			param = 1 << (be16_to_cpu(ctx->sq_crq_size) >> 11);
		else
			param = 0;
		break;
	case QP_LOG_PG_SZ:
		param = (be32_to_cpu(ctx->log_pg_sz_remote_qpn) >> 24) & 0x1f;
		param += 12;
		break;
	case QP_RQPN:
		param = be32_to_cpu(ctx->log_pg_sz_remote_qpn) & 0xffffff;
		break;
	}

out:
	kfree(out);
	return param;
}