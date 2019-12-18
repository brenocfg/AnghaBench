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
typedef  scalar_t__ u64 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx5_query_nic_system_image_guid (struct mlx5_core_dev*) ; 

__attribute__((used)) static bool same_hw_devs(struct mlx5e_priv *priv, struct mlx5e_priv *peer_priv)
{
	struct mlx5_core_dev *fmdev, *pmdev;
	u64 fsystem_guid, psystem_guid;

	fmdev = priv->mdev;
	pmdev = peer_priv->mdev;

	fsystem_guid = mlx5_query_nic_system_image_guid(fmdev);
	psystem_guid = mlx5_query_nic_system_image_guid(pmdev);

	return (fsystem_guid == psystem_guid);
}