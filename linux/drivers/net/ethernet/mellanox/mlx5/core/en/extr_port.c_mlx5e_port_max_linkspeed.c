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
struct mlx5e_port_eth_proto {int cap; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5E_PROT_MASK (int) ; 
 int MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int max (int,int const) ; 
 int mlx5_port_query_eth_proto (struct mlx5_core_dev*,int,int,struct mlx5e_port_eth_proto*) ; 
 int /*<<< orphan*/  mlx5e_port_get_speed_arr (struct mlx5_core_dev*,int const**,int*,int) ; 
 int /*<<< orphan*/  ptys_extended_ethernet ; 

int mlx5e_port_max_linkspeed(struct mlx5_core_dev *mdev, u32 *speed)
{
	struct mlx5e_port_eth_proto eproto;
	u32 max_speed = 0;
	const u32 *table;
	u32 max_size;
	bool ext;
	int err;
	int i;

	ext = MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet);
	err = mlx5_port_query_eth_proto(mdev, 1, ext, &eproto);
	if (err)
		return err;

	mlx5e_port_get_speed_arr(mdev, &table, &max_size, false);
	for (i = 0; i < max_size; ++i)
		if (eproto.cap & MLX5E_PROT_MASK(i))
			max_speed = max(max_speed, table[i]);

	*speed = max_speed;
	return 0;
}