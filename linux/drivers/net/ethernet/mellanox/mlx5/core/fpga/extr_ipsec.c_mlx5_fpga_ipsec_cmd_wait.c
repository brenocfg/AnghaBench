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
struct mlx5_fpga_ipsec_cmd_context {scalar_t__ status; int status_code; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MLX5_FPGA_CMD_TIMEOUT_MSEC ; 
 scalar_t__ MLX5_FPGA_IPSEC_CMD_COMPLETE ; 
 int /*<<< orphan*/  mlx5_fpga_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mlx5_fpga_ipsec_cmd_wait(void *ctx)
{
	struct mlx5_fpga_ipsec_cmd_context *context = ctx;
	unsigned long timeout =
		msecs_to_jiffies(MLX5_FPGA_CMD_TIMEOUT_MSEC);
	int res;

	res = wait_for_completion_timeout(&context->complete, timeout);
	if (!res) {
		mlx5_fpga_warn(context->dev, "Failure waiting for IPSec command response\n");
		return -ETIMEDOUT;
	}

	if (context->status == MLX5_FPGA_IPSEC_CMD_COMPLETE)
		res = context->status_code;
	else
		res = -EIO;

	return res;
}