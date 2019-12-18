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
struct mlx5_async_ctx {int /*<<< orphan*/  num_inflight; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void mlx5_cmd_cleanup_async_ctx(struct mlx5_async_ctx *ctx)
{
	atomic_dec(&ctx->num_inflight);
	wait_event(ctx->wait, atomic_read(&ctx->num_inflight) == 0);
}