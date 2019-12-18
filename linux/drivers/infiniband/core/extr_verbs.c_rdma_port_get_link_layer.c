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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int (* get_link_layer ) (struct ib_device*,int /*<<< orphan*/ ) ;} ;
struct ib_device {int /*<<< orphan*/  node_type; TYPE_1__ ops; } ;
typedef  enum rdma_transport_type { ____Placeholder_rdma_transport_type } rdma_transport_type ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int IB_LINK_LAYER_INFINIBAND ; 
 int RDMA_TRANSPORT_IB ; 
 int rdma_node_get_transport (int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ) ; 

enum rdma_link_layer rdma_port_get_link_layer(struct ib_device *device, u8 port_num)
{
	enum rdma_transport_type lt;
	if (device->ops.get_link_layer)
		return device->ops.get_link_layer(device, port_num);

	lt = rdma_node_get_transport(device->node_type);
	if (lt == RDMA_TRANSPORT_IB)
		return IB_LINK_LAYER_INFINIBAND;

	return IB_LINK_LAYER_ETHERNET;
}