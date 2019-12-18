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
struct rdma_counter {int /*<<< orphan*/  id; int /*<<< orphan*/  stats; scalar_t__ port; int /*<<< orphan*/  device; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_counters {int dummy; } ;

/* Variables and functions */
 struct mlx5_ib_counters* get_counters (struct mlx5_ib_dev*,scalar_t__) ; 
 int mlx5_ib_query_q_counters (int /*<<< orphan*/ ,struct mlx5_ib_counters const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_counter_update_stats(struct rdma_counter *counter)
{
	struct mlx5_ib_dev *dev = to_mdev(counter->device);
	const struct mlx5_ib_counters *cnts =
		get_counters(dev, counter->port - 1);

	return mlx5_ib_query_q_counters(dev->mdev, cnts,
					counter->stats, counter->id);
}