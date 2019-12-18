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
 int find_first_bit (unsigned long*,int) ; 
 int /*<<< orphan*/  mlx5e_port_get_speed_arr (struct mlx5_core_dev*,int const**,int*,int) ; 

u32 mlx5e_port_ptys2speed(struct mlx5_core_dev *mdev, u32 eth_proto_oper,
			  bool force_legacy)
{
	unsigned long temp = eth_proto_oper;
	const u32 *table;
	u32 speed = 0;
	u32 max_size;
	int i;

	mlx5e_port_get_speed_arr(mdev, &table, &max_size, force_legacy);
	i = find_first_bit(&temp, max_size);
	if (i < max_size)
		speed = table[i];
	return speed;
}