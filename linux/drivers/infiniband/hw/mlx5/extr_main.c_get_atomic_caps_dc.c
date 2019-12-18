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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_device_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_size_dc ; 
 int /*<<< orphan*/  get_atomic_caps (struct mlx5_ib_dev*,int /*<<< orphan*/ ,struct ib_device_attr*) ; 

__attribute__((used)) static void get_atomic_caps_dc(struct mlx5_ib_dev *dev,
			       struct ib_device_attr *props)
{
	u8 atomic_size_qp = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_dc);

	get_atomic_caps(dev, atomic_size_qp, props);
}