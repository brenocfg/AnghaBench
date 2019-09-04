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
struct mlx5_fpga_dma_buf {TYPE_1__* sg; } ;
struct mlx5_fpga_tls_command_context {struct mlx5_fpga_dma_buf buf; } ;
struct mlx5_core_dev {int /*<<< orphan*/  fpga; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {scalar_t__ size; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEARDOWN_STREAM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_TLS_COMMAND_SIZE ; 
 int /*<<< orphan*/  command_type ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct mlx5_fpga_tls_command_context* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_cmd_send (int /*<<< orphan*/ ,struct mlx5_fpga_tls_command_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_flow_to_cmd (void*,void*) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_teardown_completion ; 
 int /*<<< orphan*/  tls_cmd ; 

__attribute__((used)) static void mlx5_fpga_tls_send_teardown_cmd(struct mlx5_core_dev *mdev,
					    void *flow, u32 swid, gfp_t flags)
{
	struct mlx5_fpga_tls_command_context *ctx;
	struct mlx5_fpga_dma_buf *buf;
	void *cmd;

	ctx = kzalloc(sizeof(*ctx) + MLX5_TLS_COMMAND_SIZE, flags);
	if (!ctx)
		return;

	buf = &ctx->buf;
	cmd = (ctx + 1);
	MLX5_SET(tls_cmd, cmd, command_type, CMD_TEARDOWN_STREAM);
	MLX5_SET(tls_cmd, cmd, swid, swid);

	mlx5_fpga_tls_flow_to_cmd(flow, cmd);
	kfree(flow);

	buf->sg[0].data = cmd;
	buf->sg[0].size = MLX5_TLS_COMMAND_SIZE;

	mlx5_fpga_tls_cmd_send(mdev->fpga, ctx,
			       mlx5_fpga_tls_teardown_completion);
}