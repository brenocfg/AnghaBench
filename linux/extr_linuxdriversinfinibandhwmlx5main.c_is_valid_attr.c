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
struct mlx5_core_dev {int dummy; } ;
struct ib_flow_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_valid_ethertype (struct mlx5_core_dev*,struct ib_flow_attr const*,int) ; 

__attribute__((used)) static bool is_valid_attr(struct mlx5_core_dev *mdev,
			  const struct ib_flow_attr *flow_attr)
{
	return is_valid_ethertype(mdev, flow_attr, false) &&
	       is_valid_ethertype(mdev, flow_attr, true);
}