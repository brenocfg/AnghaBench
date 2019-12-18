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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5E_SUPPORTED_DSCP ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET16 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_REG_QPDPM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dscp ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_port ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prio ; 
 int /*<<< orphan*/  qpdpm_dscp_reg ; 
 int /*<<< orphan*/  qpdpm_reg ; 

int mlx5_query_dscp2prio(struct mlx5_core_dev *mdev, u8 *dscp2prio)
{
	int sz = MLX5_ST_SZ_BYTES(qpdpm_reg);
	void *qpdpm_dscp;
	void *out;
	void *in;
	int err;
	int i;

	in = kzalloc(sz, GFP_KERNEL);
	out = kzalloc(sz, GFP_KERNEL);
	if (!in || !out) {
		err = -ENOMEM;
		goto out;
	}

	MLX5_SET(qpdpm_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_QPDPM, 0, 0);
	if (err)
		goto out;

	for (i = 0; i < (MLX5E_SUPPORTED_DSCP); i++) {
		qpdpm_dscp = MLX5_ADDR_OF(qpdpm_reg, out, dscp[i]);
		dscp2prio[i] = MLX5_GET16(qpdpm_dscp_reg, qpdpm_dscp, prio);
	}

out:
	kfree(in);
	kfree(out);
	return err;
}