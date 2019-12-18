#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable_uc_local_lb; int /*<<< orphan*/  disable_mc_local_lb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MC_LOCAL_LB ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int UC_LOCAL_LB ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_query_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 

int mlx5_nic_vport_query_local_lb(struct mlx5_core_dev *mdev, bool *status)
{
	int outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	u32 *out;
	int value;
	int err;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out, outlen);
	if (err)
		goto out;

	value = MLX5_GET(query_nic_vport_context_out, out,
			 nic_vport_context.disable_mc_local_lb) << MC_LOCAL_LB;

	value |= MLX5_GET(query_nic_vport_context_out, out,
			  nic_vport_context.disable_uc_local_lb) << UC_LOCAL_LB;

	*status = !value;

out:
	kfree(out);
	return err;
}