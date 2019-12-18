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
struct postsend_info {int /*<<< orphan*/  read; int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  write; } ;
struct mlx5dr_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_OPCODE_RDMA_READ ; 
 int /*<<< orphan*/  MLX5_OPCODE_RDMA_WRITE ; 
 int /*<<< orphan*/  dr_rdma_segments (struct mlx5dr_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dr_post_send(struct mlx5dr_qp *dr_qp, struct postsend_info *send_info)
{
	dr_rdma_segments(dr_qp, send_info->remote_addr, send_info->rkey,
			 &send_info->write, MLX5_OPCODE_RDMA_WRITE, 0);
	dr_rdma_segments(dr_qp, send_info->remote_addr, send_info->rkey,
			 &send_info->read, MLX5_OPCODE_RDMA_READ, 1);
}