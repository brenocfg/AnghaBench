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
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int MLX5E_NUM_TUNNEL_TT ; 
 scalar_t__ mlx5e_tunnel_proto_supported (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ttc_tunnel_rules ; 

bool mlx5e_any_tunnel_proto_supported(struct mlx5_core_dev *mdev)
{
	int tt;

	for (tt = 0; tt < MLX5E_NUM_TUNNEL_TT; tt++) {
		if (mlx5e_tunnel_proto_supported(mdev, ttc_tunnel_rules[tt].proto))
			return true;
	}
	return false;
}