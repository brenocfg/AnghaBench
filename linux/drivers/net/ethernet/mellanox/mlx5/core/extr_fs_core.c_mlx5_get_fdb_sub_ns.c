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
struct mlx5_flow_steering {struct mlx5_flow_namespace** fdb_sub_ns; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct TYPE_2__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */

struct mlx5_flow_namespace *mlx5_get_fdb_sub_ns(struct mlx5_core_dev *dev,
						int n)
{
	struct mlx5_flow_steering *steering = dev->priv.steering;

	if (!steering || !steering->fdb_sub_ns)
		return NULL;

	return steering->fdb_sub_ns[n];
}