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
struct TYPE_2__ {int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {TYPE_1__ global; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_attr {scalar_t__ subnet_prefix; } ;
struct ib_device {int (* query_port ) (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ;int (* query_gid ) (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_gid*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int stub2 (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_gid*) ; 

int ib_query_port(struct ib_device *device,
		  u8 port_num,
		  struct ib_port_attr *port_attr)
{
	union ib_gid gid;
	int err;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	memset(port_attr, 0, sizeof(*port_attr));
	err = device->query_port(device, port_num, port_attr);
	if (err || port_attr->subnet_prefix)
		return err;

	if (rdma_port_get_link_layer(device, port_num) != IB_LINK_LAYER_INFINIBAND)
		return 0;

	err = device->query_gid(device, port_num, 0, &gid);
	if (err)
		return err;

	port_attr->subnet_prefix = be64_to_cpu(gid.global.subnet_prefix);
	return 0;
}