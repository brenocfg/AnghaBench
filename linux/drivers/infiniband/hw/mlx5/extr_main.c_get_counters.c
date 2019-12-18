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
typedef  size_t u8 ;
struct mlx5_ib_dev {TYPE_1__* port; int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_counters {int dummy; } ;
struct TYPE_2__ {struct mlx5_ib_counters const cnts; } ;

/* Variables and functions */
 scalar_t__ is_mdev_switchdev_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct mlx5_ib_counters *get_counters(struct mlx5_ib_dev *dev,
						   u8 port_num)
{
	return is_mdev_switchdev_mode(dev->mdev) ? &dev->port[0].cnts :
						   &dev->port[port_num].cnts;
}