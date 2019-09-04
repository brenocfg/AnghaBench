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
typedef  int /*<<< orphan*/  u32 ;
struct tls_crypto_info {int dummy; } ;
struct mlx5_setup_stream_context {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_TLS_COMMAND_SIZE ; 
 int /*<<< orphan*/  kfree (struct mlx5_setup_stream_context*) ; 
 struct mlx5_setup_stream_context* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_device_caps (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_flow_to_cmd (void*,void*) ; 
 int mlx5_fpga_tls_set_key_material (void*,int /*<<< orphan*/ ,struct tls_crypto_info*) ; 
 int mlx5_fpga_tls_setup_stream_cmd (struct mlx5_core_dev*,struct mlx5_setup_stream_context*) ; 
 int /*<<< orphan*/  tls_cmd ; 

__attribute__((used)) static int _mlx5_fpga_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
				   struct tls_crypto_info *crypto_info,
				   u32 swid, u32 tcp_sn)
{
	u32 caps = mlx5_fpga_tls_device_caps(mdev);
	struct mlx5_setup_stream_context *ctx;
	int ret = -ENOMEM;
	size_t cmd_size;
	void *cmd;

	cmd_size = MLX5_TLS_COMMAND_SIZE + sizeof(*ctx);
	ctx = kzalloc(cmd_size, GFP_KERNEL);
	if (!ctx)
		goto out;

	cmd = ctx + 1;
	ret = mlx5_fpga_tls_set_key_material(cmd, caps, crypto_info);
	if (ret)
		goto free_ctx;

	mlx5_fpga_tls_flow_to_cmd(flow, cmd);

	MLX5_SET(tls_cmd, cmd, swid, swid);
	MLX5_SET(tls_cmd, cmd, tcp_sn, tcp_sn);

	return mlx5_fpga_tls_setup_stream_cmd(mdev, ctx);

free_ctx:
	kfree(ctx);
out:
	return ret;
}