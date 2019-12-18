#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_devcom {TYPE_2__* priv; } ;
typedef  enum mlx5_devcom_components { ____Placeholder_mlx5_devcom_components } mlx5_devcom_components ;
struct TYPE_4__ {TYPE_1__* components; } ;
struct TYPE_3__ {int paired; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_devcom*) ; 

bool mlx5_devcom_is_paired(struct mlx5_devcom *devcom,
			   enum mlx5_devcom_components id)
{
	if (IS_ERR_OR_NULL(devcom))
		return false;

	return devcom->priv->components[id].paired;
}