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
struct mlx5_devcom_component {int /*<<< orphan*/  sem; TYPE_2__* device; } ;
struct mlx5_devcom {size_t idx; TYPE_1__* priv; } ;
typedef  enum mlx5_devcom_components { ____Placeholder_mlx5_devcom_components } mlx5_devcom_components ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {struct mlx5_devcom_component* components; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_devcom*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mlx5_devcom_unregister_component(struct mlx5_devcom *devcom,
				      enum mlx5_devcom_components id)
{
	struct mlx5_devcom_component *comp;

	if (IS_ERR_OR_NULL(devcom))
		return;

	comp = &devcom->priv->components[id];
	down_write(&comp->sem);
	comp->device[devcom->idx].data = NULL;
	up_write(&comp->sem);
}