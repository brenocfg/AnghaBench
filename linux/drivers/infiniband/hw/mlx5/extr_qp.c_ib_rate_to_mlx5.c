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
typedef  int u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_RATE_2_5_GBPS ; 
 int IB_RATE_600_GBPS ; 
 int IB_RATE_PORT_CURRENT ; 
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_STAT_RATE_OFFSET ; 
 int /*<<< orphan*/  stat_rate_support ; 

__attribute__((used)) static int ib_rate_to_mlx5(struct mlx5_ib_dev *dev, u8 rate)
{
	if (rate == IB_RATE_PORT_CURRENT)
		return 0;

	if (rate < IB_RATE_2_5_GBPS || rate > IB_RATE_600_GBPS)
		return -EINVAL;

	while (rate != IB_RATE_PORT_CURRENT &&
	       !(1 << (rate + MLX5_STAT_RATE_OFFSET) &
		 MLX5_CAP_GEN(dev->mdev, stat_rate_support)))
		--rate;

	return rate ? rate + MLX5_STAT_RATE_OFFSET : rate;
}