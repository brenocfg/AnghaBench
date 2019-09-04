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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_INFINIBAND_PORT_COUNTERS_GROUP ; 
 int /*<<< orphan*/  MLX5_REG_PPCNT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grp ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_port ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,size_t,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppcnt_reg ; 

int mlx5_core_query_ib_ppcnt(struct mlx5_core_dev *dev,
			     u8 port_num, void *out, size_t sz)
{
	u32 *in;
	int err;

	in  = kvzalloc(sz, GFP_KERNEL);
	if (!in) {
		err = -ENOMEM;
		return err;
	}

	MLX5_SET(ppcnt_reg, in, local_port, port_num);

	MLX5_SET(ppcnt_reg, in, grp, MLX5_INFINIBAND_PORT_COUNTERS_GROUP);
	err = mlx5_core_access_reg(dev, in, sz, out,
				   sz, MLX5_REG_PPCNT, 0, 0);

	kvfree(in);
	return err;
}