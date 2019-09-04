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
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  ets; int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct ieee_ets {int /*<<< orphan*/  prio_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee_ets*,int) ; 
 int mlx4_SET_PORT_PRIO2TC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_en_config_port_scheduler (struct mlx4_en_priv*,struct ieee_ets*,int /*<<< orphan*/ *) ; 
 int mlx4_en_ets_validate (struct mlx4_en_priv*,struct ieee_ets*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mlx4_en_dcbnl_ieee_setets(struct net_device *dev, struct ieee_ets *ets)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;

	err = mlx4_en_ets_validate(priv, ets);
	if (err)
		return err;

	err = mlx4_SET_PORT_PRIO2TC(mdev->dev, priv->port, ets->prio_tc);
	if (err)
		return err;

	err = mlx4_en_config_port_scheduler(priv, ets, NULL);
	if (err)
		return err;

	memcpy(&priv->ets, ets, sizeof(priv->ets));

	return 0;
}