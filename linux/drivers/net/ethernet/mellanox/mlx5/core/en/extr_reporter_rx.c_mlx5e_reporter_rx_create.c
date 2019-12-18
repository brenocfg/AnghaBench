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
struct mlx5e_priv {struct devlink_health_reporter* rx_reporter; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdev; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  MLX5E_REPORTER_RX_GRACEFUL_PERIOD ; 
 int PTR_ERR (struct devlink_health_reporter*) ; 
 struct devlink_health_reporter* devlink_health_reporter_create (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5_rx_reporter_ops ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

int mlx5e_reporter_rx_create(struct mlx5e_priv *priv)
{
	struct devlink *devlink = priv_to_devlink(priv->mdev);
	struct devlink_health_reporter *reporter;

	reporter = devlink_health_reporter_create(devlink,
						  &mlx5_rx_reporter_ops,
						  MLX5E_REPORTER_RX_GRACEFUL_PERIOD,
						  true, priv);
	if (IS_ERR(reporter)) {
		netdev_warn(priv->netdev, "Failed to create rx reporter, err = %ld\n",
			    PTR_ERR(reporter));
		return PTR_ERR(reporter);
	}
	priv->rx_reporter = reporter;
	return 0;
}