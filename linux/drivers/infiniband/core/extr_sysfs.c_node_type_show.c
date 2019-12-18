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
struct ib_device {int node_type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  RDMA_NODE_IB_CA 134 
#define  RDMA_NODE_IB_ROUTER 133 
#define  RDMA_NODE_IB_SWITCH 132 
#define  RDMA_NODE_RNIC 131 
#define  RDMA_NODE_UNSPECIFIED 130 
#define  RDMA_NODE_USNIC 129 
#define  RDMA_NODE_USNIC_UDP 128 
 struct ib_device* rdma_device_to_ibdev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t node_type_show(struct device *device,
			      struct device_attribute *attr, char *buf)
{
	struct ib_device *dev = rdma_device_to_ibdev(device);

	switch (dev->node_type) {
	case RDMA_NODE_IB_CA:	  return sprintf(buf, "%d: CA\n", dev->node_type);
	case RDMA_NODE_RNIC:	  return sprintf(buf, "%d: RNIC\n", dev->node_type);
	case RDMA_NODE_USNIC:	  return sprintf(buf, "%d: usNIC\n", dev->node_type);
	case RDMA_NODE_USNIC_UDP: return sprintf(buf, "%d: usNIC UDP\n", dev->node_type);
	case RDMA_NODE_UNSPECIFIED: return sprintf(buf, "%d: unspecified\n", dev->node_type);
	case RDMA_NODE_IB_SWITCH: return sprintf(buf, "%d: switch\n", dev->node_type);
	case RDMA_NODE_IB_ROUTER: return sprintf(buf, "%d: router\n", dev->node_type);
	default:		  return sprintf(buf, "%d: <unknown>\n", dev->node_type);
	}
}