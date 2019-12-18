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
struct mlx5e_rep_priv {int /*<<< orphan*/  dl_port; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_port_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ is_devlink_port_supported (struct mlx5_core_dev*,struct mlx5e_rep_priv*) ; 

__attribute__((used)) static void unregister_devlink_port(struct mlx5_core_dev *dev,
				    struct mlx5e_rep_priv *rpriv)
{
	if (is_devlink_port_supported(dev, rpriv))
		devlink_port_unregister(&rpriv->dl_port);
}