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
struct mlx5_devcom_list {size_t idx; int /*<<< orphan*/  list; int /*<<< orphan*/ ** devs; struct mlx5_devcom_list* priv; } ;
struct mlx5_devcom {size_t idx; int /*<<< orphan*/  list; int /*<<< orphan*/ ** devs; struct mlx5_devcom* priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_devcom_list*) ; 
 int MLX5_MAX_PORTS ; 
 int /*<<< orphan*/  kfree (struct mlx5_devcom_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void mlx5_devcom_unregister_device(struct mlx5_devcom *devcom)
{
	struct mlx5_devcom_list *priv;
	int i;

	if (IS_ERR_OR_NULL(devcom))
		return;

	priv = devcom->priv;
	priv->devs[devcom->idx] = NULL;

	kfree(devcom);

	for (i = 0; i < MLX5_MAX_PORTS; i++)
		if (priv->devs[i])
			break;

	if (i != MLX5_MAX_PORTS)
		return;

	list_del(&priv->list);
	kfree(priv);
}