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
struct mlx5_read_counters_attr {int /*<<< orphan*/ * out; struct mlx5_fc* hw_cntrs_hndl; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_fc {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 size_t IB_COUNTER_BYTES ; 
 size_t IB_COUNTER_PACKETS ; 
 int mlx5_fc_query (int /*<<< orphan*/ ,struct mlx5_fc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int read_flow_counters(struct ib_device *ibdev,
			      struct mlx5_read_counters_attr *read_attr)
{
	struct mlx5_fc *fc = read_attr->hw_cntrs_hndl;
	struct mlx5_ib_dev *dev = to_mdev(ibdev);

	return mlx5_fc_query(dev->mdev, fc,
			     &read_attr->out[IB_COUNTER_PACKETS],
			     &read_attr->out[IB_COUNTER_BYTES]);
}