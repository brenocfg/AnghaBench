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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_TX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_modify_header_actions ; 

__attribute__((used)) static bool mlx5_ib_modify_header_supported(struct mlx5_ib_dev *dev)
{
	return MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
					 max_modify_header_actions) ||
	       MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev, max_modify_header_actions);
}