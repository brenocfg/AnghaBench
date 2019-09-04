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
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int IB_LINK_LAYER_INFINIBAND ; 
 int IB_LINK_LAYER_UNSPECIFIED ; 
#define  MLX5_CAP_PORT_TYPE_ETH 129 
#define  MLX5_CAP_PORT_TYPE_IB 128 

__attribute__((used)) static enum rdma_link_layer
mlx5_port_type_cap_to_rdma_ll(int port_type_cap)
{
	switch (port_type_cap) {
	case MLX5_CAP_PORT_TYPE_IB:
		return IB_LINK_LAYER_INFINIBAND;
	case MLX5_CAP_PORT_TYPE_ETH:
		return IB_LINK_LAYER_ETHERNET;
	default:
		return IB_LINK_LAYER_UNSPECIFIED;
	}
}