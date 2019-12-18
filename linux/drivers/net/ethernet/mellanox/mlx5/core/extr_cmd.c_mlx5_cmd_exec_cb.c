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
struct mlx5_async_work {int /*<<< orphan*/  user_callback; struct mlx5_async_ctx* ctx; } ;
struct mlx5_async_ctx {int /*<<< orphan*/  wait; int /*<<< orphan*/  num_inflight; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  mlx5_async_cbk_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int cmd_exec (int /*<<< orphan*/ ,void*,int,void*,int,int /*<<< orphan*/ ,struct mlx5_async_work*,int) ; 
 int /*<<< orphan*/  mlx5_cmd_exec_cb_handler ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int mlx5_cmd_exec_cb(struct mlx5_async_ctx *ctx, void *in, int in_size,
		     void *out, int out_size, mlx5_async_cbk_t callback,
		     struct mlx5_async_work *work)
{
	int ret;

	work->ctx = ctx;
	work->user_callback = callback;
	if (WARN_ON(!atomic_inc_not_zero(&ctx->num_inflight)))
		return -EIO;
	ret = cmd_exec(ctx->dev, in, in_size, out, out_size,
		       mlx5_cmd_exec_cb_handler, work, false);
	if (ret && atomic_dec_and_test(&ctx->num_inflight))
		wake_up(&ctx->wait);

	return ret;
}