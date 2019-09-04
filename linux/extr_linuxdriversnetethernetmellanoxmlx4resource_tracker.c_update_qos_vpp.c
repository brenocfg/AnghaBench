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
struct mlx4_vf_immed_vlan_work {int /*<<< orphan*/  qos_vport; } ;
struct TYPE_2__ {int /*<<< orphan*/  qos_vport; } ;
struct mlx4_update_qp_context {TYPE_1__ qp_context; int /*<<< orphan*/  qp_mask; } ;

/* Variables and functions */
 unsigned long long MLX4_UPD_QP_MASK_QOS_VPP ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long long) ; 

__attribute__((used)) static void update_qos_vpp(struct mlx4_update_qp_context *ctx,
			   struct mlx4_vf_immed_vlan_work *work)
{
	ctx->qp_mask |= cpu_to_be64(1ULL << MLX4_UPD_QP_MASK_QOS_VPP);
	ctx->qp_context.qos_vport = work->qos_vport;
}