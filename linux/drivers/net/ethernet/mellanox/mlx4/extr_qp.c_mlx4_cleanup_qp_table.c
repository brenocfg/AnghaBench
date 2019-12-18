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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_CONF_SPECIAL_QP (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cleanup_qp_zones (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 

void mlx4_cleanup_qp_table(struct mlx4_dev *dev)
{
	if (mlx4_is_slave(dev))
		return;

	mlx4_CONF_SPECIAL_QP(dev, 0);

	mlx4_cleanup_qp_zones(dev);
}