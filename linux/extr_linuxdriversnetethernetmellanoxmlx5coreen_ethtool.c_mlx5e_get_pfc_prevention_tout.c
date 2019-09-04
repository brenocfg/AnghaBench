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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_DEBUG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_query_port_stall_watermark (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pfcc_mask ; 
 int /*<<< orphan*/  stall_detect ; 

__attribute__((used)) static int mlx5e_get_pfc_prevention_tout(struct net_device *netdev,
					 u16 *pfc_prevention_tout)
{
	struct mlx5e_priv *priv    = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;

	if (!MLX5_CAP_PCAM_FEATURE((priv)->mdev, pfcc_mask) ||
	    !MLX5_CAP_DEBUG((priv)->mdev, stall_detect))
		return -EOPNOTSUPP;

	return mlx5_query_port_stall_watermark(mdev, pfc_prevention_tout, NULL);
}