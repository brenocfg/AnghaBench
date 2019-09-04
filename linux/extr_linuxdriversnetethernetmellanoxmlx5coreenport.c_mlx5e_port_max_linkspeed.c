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
typedef  int u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5E_LINK_MODES_NUMBER ; 
 int MLX5E_PROT_MASK (int) ; 
 int /*<<< orphan*/  MLX5_PTYS_EN ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int mlx5_query_port_proto_cap (struct mlx5_core_dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5e_link_speed ; 

int mlx5e_port_max_linkspeed(struct mlx5_core_dev *mdev, u32 *speed)
{
	u32 max_speed = 0;
	u32 proto_cap;
	int err;
	int i;

	err = mlx5_query_port_proto_cap(mdev, &proto_cap, MLX5_PTYS_EN);
	if (err)
		return err;

	for (i = 0; i < MLX5E_LINK_MODES_NUMBER; ++i)
		if (proto_cap & MLX5E_PROT_MASK(i))
			max_speed = max(max_speed, mlx5e_link_speed[i]);

	*speed = max_speed;
	return 0;
}