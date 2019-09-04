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
struct ib_device {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask const* mlx5_get_vector_affinity_hint (int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static const struct cpumask *
mlx5_ib_get_vector_affinity(struct ib_device *ibdev, int comp_vector)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);

	return mlx5_get_vector_affinity_hint(dev->mdev, comp_vector);
}