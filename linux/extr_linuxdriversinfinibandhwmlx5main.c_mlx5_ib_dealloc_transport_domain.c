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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {int user_td; int /*<<< orphan*/  lb_mutex; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  disable_local_lb_mc ; 
 int /*<<< orphan*/  disable_local_lb_uc ; 
 int /*<<< orphan*/  log_max_transport_domain ; 
 int /*<<< orphan*/  mlx5_core_dealloc_transport_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_nic_vport_update_local_lb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static void mlx5_ib_dealloc_transport_domain(struct mlx5_ib_dev *dev, u32 tdn)
{
	if (!MLX5_CAP_GEN(dev->mdev, log_max_transport_domain))
		return;

	mlx5_core_dealloc_transport_domain(dev->mdev, tdn);

	if ((MLX5_CAP_GEN(dev->mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH) ||
	    (!MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) &&
	     !MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		return;

	mutex_lock(&dev->lb_mutex);
	dev->user_td--;

	if (dev->user_td < 2)
		mlx5_nic_vport_update_local_lb(dev->mdev, false);

	mutex_unlock(&dev->lb_mutex);
}