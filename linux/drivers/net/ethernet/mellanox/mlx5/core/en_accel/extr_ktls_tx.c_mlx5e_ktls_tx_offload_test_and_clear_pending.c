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
struct mlx5e_ktls_offload_context_tx {int ctx_post_pending; } ;

/* Variables and functions */

__attribute__((used)) static bool
mlx5e_ktls_tx_offload_test_and_clear_pending(struct mlx5e_ktls_offload_context_tx *priv_tx)
{
	bool ret = priv_tx->ctx_post_pending;

	priv_tx->ctx_post_pending = false;

	return ret;
}