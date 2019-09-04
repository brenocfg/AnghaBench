#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rdma_hw_stats {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_ext_ppcnt_counters; scalar_t__ num_cong_counters; scalar_t__ num_q_counters; int /*<<< orphan*/  names; } ;
struct mlx5_ib_port {TYPE_1__ cnts; } ;
struct mlx5_ib_dev {struct mlx5_ib_port* port; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_HW_STATS_DEFAULT_LIFESPAN ; 
 struct rdma_hw_stats* rdma_alloc_hw_stats_struct (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct rdma_hw_stats *mlx5_ib_alloc_hw_stats(struct ib_device *ibdev,
						    u8 port_num)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);
	struct mlx5_ib_port *port = &dev->port[port_num - 1];

	/* We support only per port stats */
	if (port_num == 0)
		return NULL;

	return rdma_alloc_hw_stats_struct(port->cnts.names,
					  port->cnts.num_q_counters +
					  port->cnts.num_cong_counters +
					  port->cnts.num_ext_ppcnt_counters,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
}