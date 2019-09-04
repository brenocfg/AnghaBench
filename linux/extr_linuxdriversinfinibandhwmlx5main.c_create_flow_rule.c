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
struct mlx5_ib_flow_prio {int dummy; } ;
struct mlx5_ib_flow_handler {int dummy; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_flow_destination {int dummy; } ;
struct ib_flow_attr {int dummy; } ;

/* Variables and functions */
 struct mlx5_ib_flow_handler* _create_flow_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr const*,struct mlx5_flow_destination*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_ib_flow_handler *create_flow_rule(struct mlx5_ib_dev *dev,
						     struct mlx5_ib_flow_prio *ft_prio,
						     const struct ib_flow_attr *flow_attr,
						     struct mlx5_flow_destination *dst)
{
	return _create_flow_rule(dev, ft_prio, flow_attr, dst, 0, NULL);
}