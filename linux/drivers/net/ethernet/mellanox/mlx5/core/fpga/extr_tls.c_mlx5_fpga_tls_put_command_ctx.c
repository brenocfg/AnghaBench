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
struct mlx5_fpga_tls_command_context {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_fpga_tls_command_context*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5_fpga_tls_put_command_ctx(struct mlx5_fpga_tls_command_context *ctx)
{
	if (refcount_dec_and_test(&ctx->ref))
		kfree(ctx);
}