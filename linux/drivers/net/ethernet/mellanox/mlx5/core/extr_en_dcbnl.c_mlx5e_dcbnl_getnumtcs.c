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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  DCB_NUMTCS_ATTR_PFC 129 
#define  DCB_NUMTCS_ATTR_PG 128 
 int EINVAL ; 
 int /*<<< orphan*/  mlx5_max_tc (struct mlx5_core_dev*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_dcbnl_getnumtcs(struct net_device *netdev,
				 int tcs_id, u8 *num)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;

	switch (tcs_id) {
	case DCB_NUMTCS_ATTR_PG:
	case DCB_NUMTCS_ATTR_PFC:
		*num = mlx5_max_tc(mdev) + 1;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}