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
struct rdma_counter {int /*<<< orphan*/  id; int /*<<< orphan*/  device; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_core_dealloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_counter_dealloc(struct rdma_counter *counter)
{
	struct mlx5_ib_dev *dev = to_mdev(counter->device);

	return mlx5_core_dealloc_q_counter(dev->mdev, counter->id);
}