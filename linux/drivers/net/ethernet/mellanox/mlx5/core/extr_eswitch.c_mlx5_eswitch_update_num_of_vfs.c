#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int num_vfs; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_1__ esw_funcs; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_num_of_vfs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/  const*) ; 
 scalar_t__ MLX5_ESWITCH_NONE ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_2__ host_params_context ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mlx5_core_is_ecpf_esw_manager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_esw_query_functions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_esw_functions_out ; 

void mlx5_eswitch_update_num_of_vfs(struct mlx5_eswitch *esw, const int num_vfs)
{
	const u32 *out;

	WARN_ON_ONCE(esw->mode != MLX5_ESWITCH_NONE);

	if (!mlx5_core_is_ecpf_esw_manager(esw->dev)) {
		esw->esw_funcs.num_vfs = num_vfs;
		return;
	}

	out = mlx5_esw_query_functions(esw->dev);
	if (IS_ERR(out))
		return;

	esw->esw_funcs.num_vfs = MLX5_GET(query_esw_functions_out, out,
					  host_params_context.host_num_of_vfs);
	kvfree(out);
}