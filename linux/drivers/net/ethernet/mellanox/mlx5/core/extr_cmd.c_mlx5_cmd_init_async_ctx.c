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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_async_ctx {int /*<<< orphan*/  wait; int /*<<< orphan*/  num_inflight; struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

void mlx5_cmd_init_async_ctx(struct mlx5_core_dev *dev,
			     struct mlx5_async_ctx *ctx)
{
	ctx->dev = dev;
	/* Starts at 1 to avoid doing wake_up if we are not cleaning up */
	atomic_set(&ctx->num_inflight, 1);
	init_waitqueue_head(&ctx->wait);
}