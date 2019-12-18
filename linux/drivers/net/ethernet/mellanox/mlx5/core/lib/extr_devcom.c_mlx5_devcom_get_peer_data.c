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
struct mlx5_devcom_component {TYPE_1__* device; int /*<<< orphan*/  sem; int /*<<< orphan*/  paired; } ;
struct mlx5_devcom {int idx; TYPE_2__* priv; } ;
typedef  enum mlx5_devcom_components { ____Placeholder_mlx5_devcom_components } mlx5_devcom_components ;
struct TYPE_4__ {struct mlx5_devcom_component* components; } ;
struct TYPE_3__ {void* data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_devcom*) ; 
 int MLX5_MAX_PORTS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void *mlx5_devcom_get_peer_data(struct mlx5_devcom *devcom,
				enum mlx5_devcom_components id)
{
	struct mlx5_devcom_component *comp;
	int i;

	if (IS_ERR_OR_NULL(devcom))
		return NULL;

	comp = &devcom->priv->components[id];
	down_read(&comp->sem);
	if (!comp->paired) {
		up_read(&comp->sem);
		return NULL;
	}

	for (i = 0; i < MLX5_MAX_PORTS; i++)
		if (i != devcom->idx)
			break;

	return comp->device[i].data;
}