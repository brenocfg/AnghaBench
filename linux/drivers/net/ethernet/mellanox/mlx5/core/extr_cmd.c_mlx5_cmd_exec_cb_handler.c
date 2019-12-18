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
struct mlx5_async_work {int /*<<< orphan*/  (* user_callback ) (int,struct mlx5_async_work*) ;struct mlx5_async_ctx* ctx; } ;
struct mlx5_async_ctx {int /*<<< orphan*/  wait; int /*<<< orphan*/  num_inflight; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,struct mlx5_async_work*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_cmd_exec_cb_handler(int status, void *_work)
{
	struct mlx5_async_work *work = _work;
	struct mlx5_async_ctx *ctx = work->ctx;

	work->user_callback(status, work);
	if (atomic_dec_and_test(&ctx->num_inflight))
		wake_up(&ctx->wait);
}