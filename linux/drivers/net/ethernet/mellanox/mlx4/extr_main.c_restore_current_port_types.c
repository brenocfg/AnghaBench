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
struct mlx4_priv {int /*<<< orphan*/  port_mutex; } ;
struct TYPE_2__ {int num_ports; int* possible_type; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_port_type { ____Placeholder_mlx4_port_type } mlx4_port_type ;

/* Variables and functions */
 int mlx4_change_port_types (struct mlx4_dev*,int*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_start_sense (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_stop_sense (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int restore_current_port_types(struct mlx4_dev *dev,
				      enum mlx4_port_type *types,
				      enum mlx4_port_type *poss_types)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err, i;

	mlx4_stop_sense(dev);

	mutex_lock(&priv->port_mutex);
	for (i = 0; i < dev->caps.num_ports; i++)
		dev->caps.possible_type[i + 1] = poss_types[i];
	err = mlx4_change_port_types(dev, types);
	mlx4_start_sense(dev);
	mutex_unlock(&priv->port_mutex);

	return err;
}