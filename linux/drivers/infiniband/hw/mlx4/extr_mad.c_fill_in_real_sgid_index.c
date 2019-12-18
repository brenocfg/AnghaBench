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
struct rdma_ah_attr {int dummy; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; } ;
struct ib_global_route {int sgid_index; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 scalar_t__ get_slave_base_gid_ix (struct mlx4_ib_dev*,int,int) ; 
 struct ib_global_route* rdma_ah_retrieve_grh (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill_in_real_sgid_index(struct mlx4_ib_dev *dev, int slave, int port,
				    struct rdma_ah_attr *ah_attr)
{
	struct ib_global_route *grh = rdma_ah_retrieve_grh(ah_attr);
	if (rdma_port_get_link_layer(&dev->ib_dev, port) == IB_LINK_LAYER_INFINIBAND)
		grh->sgid_index = slave;
	else
		grh->sgid_index += get_slave_base_gid_ix(dev, slave, port);
}