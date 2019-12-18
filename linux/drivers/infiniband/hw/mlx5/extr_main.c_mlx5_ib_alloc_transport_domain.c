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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  disable_local_lb_mc ; 
 int /*<<< orphan*/  disable_local_lb_uc ; 
 int /*<<< orphan*/  log_max_transport_domain ; 
 int mlx5_cmd_alloc_transport_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlx5_ib_enable_lb (struct mlx5_ib_dev*,int,int) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static int mlx5_ib_alloc_transport_domain(struct mlx5_ib_dev *dev, u32 *tdn,
					  u16 uid)
{
	int err;

	if (!MLX5_CAP_GEN(dev->mdev, log_max_transport_domain))
		return 0;

	err = mlx5_cmd_alloc_transport_domain(dev->mdev, tdn, uid);
	if (err)
		return err;

	if ((MLX5_CAP_GEN(dev->mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH) ||
	    (!MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) &&
	     !MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		return err;

	return mlx5_ib_enable_lb(dev, true, false);
}