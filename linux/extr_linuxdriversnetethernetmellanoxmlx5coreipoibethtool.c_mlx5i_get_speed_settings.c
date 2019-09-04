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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 int mlx5_ptys_rate_enum_to_int (int /*<<< orphan*/ ) ; 
 int mlx5_ptys_width_enum_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5i_get_speed_settings(u16 ib_link_width_oper, u16 ib_proto_oper)
{
	int rate, width;

	rate = mlx5_ptys_rate_enum_to_int(ib_proto_oper);
	if (rate < 0)
		return -EINVAL;
	width = mlx5_ptys_width_enum_to_int(ib_link_width_oper);
	if (width < 0)
		return -EINVAL;

	return rate * width;
}