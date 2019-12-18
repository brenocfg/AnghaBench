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
struct mlx5e_ktls_offload_context_tx {int /*<<< orphan*/  tisn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_NO_OFFLOAD ; 
 int /*<<< orphan*/  MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_START ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_state ; 
 int /*<<< orphan*/  record_tracker_state ; 
 int /*<<< orphan*/  tisn ; 
 int /*<<< orphan*/  tls_progress_params ; 

__attribute__((used)) static void
fill_progress_params_ctx(void *ctx, struct mlx5e_ktls_offload_context_tx *priv_tx)
{
	MLX5_SET(tls_progress_params, ctx, tisn, priv_tx->tisn);
	MLX5_SET(tls_progress_params, ctx, record_tracker_state,
		 MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_START);
	MLX5_SET(tls_progress_params, ctx, auth_state,
		 MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_NO_OFFLOAD);
}