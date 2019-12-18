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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int flags; TYPE_1__* mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DCB_NUMTCS_ATTR_PFC ; 
 int EINVAL ; 
 int MLX4_EN_FLAG_DCB_ENABLED ; 
 int /*<<< orphan*/  mlx4_max_tc (int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_dcbnl_getnumtcs(struct net_device *netdev, int tcid, u8 *num)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);

	if (!(priv->flags & MLX4_EN_FLAG_DCB_ENABLED))
		return -EINVAL;

	if (tcid == DCB_NUMTCS_ATTR_PFC)
		*num = mlx4_max_tc(priv->mdev->dev);
	else
		*num = 0;

	return 0;
}