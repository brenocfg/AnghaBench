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
struct mlx4_priv {int* def_counter; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_get_default_counter_index(struct mlx4_dev *dev, int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	return priv->def_counter[port - 1];
}