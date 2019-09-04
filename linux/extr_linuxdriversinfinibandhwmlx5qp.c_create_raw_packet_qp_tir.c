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
typedef  int u32 ;
struct TYPE_3__ {int qpn; } ;
struct TYPE_4__ {TYPE_1__ mqp; } ;
struct mlx5_ib_rq {int /*<<< orphan*/  tirn; TYPE_2__ base; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; scalar_t__ rep; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_TIRC_DISP_TYPE_DIRECT ; 
 int MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST_ ; 
 int /*<<< orphan*/  create_tir_in ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  disp_type ; 
 int /*<<< orphan*/  inline_rqn ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 int* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_tir (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  self_lb_block ; 
 int /*<<< orphan*/  transport_domain ; 
 int /*<<< orphan*/  tunneled_offload_en ; 

__attribute__((used)) static int create_raw_packet_qp_tir(struct mlx5_ib_dev *dev,
				    struct mlx5_ib_rq *rq, u32 tdn,
				    bool tunnel_offload_en)
{
	u32 *in;
	void *tirc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_DIRECT);
	MLX5_SET(tirc, tirc, inline_rqn, rq->base.mqp.qpn);
	MLX5_SET(tirc, tirc, transport_domain, tdn);
	if (tunnel_offload_en)
		MLX5_SET(tirc, tirc, tunneled_offload_en, 1);

	if (dev->rep)
		MLX5_SET(tirc, tirc, self_lb_block,
			 MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST_);

	err = mlx5_core_create_tir(dev->mdev, in, inlen, &rq->tirn);

	kvfree(in);

	return err;
}