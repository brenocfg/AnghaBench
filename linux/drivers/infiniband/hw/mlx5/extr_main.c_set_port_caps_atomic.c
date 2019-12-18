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
typedef  int u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_hca_vport_context {int cap_mask1_perm; int cap_mask1; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int mlx5_core_modify_hca_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_hca_vport_context*) ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 
 int mlx5_query_hca_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_hca_vport_context*) ; 

__attribute__((used)) static int set_port_caps_atomic(struct mlx5_ib_dev *dev, u8 port_num, u32 mask,
				u32 value)
{
	struct mlx5_hca_vport_context ctx = {};
	struct mlx5_core_dev *mdev;
	u8 mdev_port_num;
	int err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port_num, &mdev_port_num);
	if (!mdev)
		return -ENODEV;

	err = mlx5_query_hca_vport_context(mdev, 0, mdev_port_num, 0, &ctx);
	if (err)
		goto out;

	if (~ctx.cap_mask1_perm & mask) {
		mlx5_ib_warn(dev, "trying to change bitmask 0x%X but change supported 0x%X\n",
			     mask, ctx.cap_mask1_perm);
		err = -EINVAL;
		goto out;
	}

	ctx.cap_mask1 = value;
	ctx.cap_mask1_perm = mask;
	err = mlx5_core_modify_hca_vport_context(mdev, 0, mdev_port_num,
						 0, &ctx);

out:
	mlx5_ib_put_native_port_mdev(dev, port_num);

	return err;
}