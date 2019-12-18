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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFLA_VF_IB_NODE_GUID ; 
 int IFLA_VF_IB_PORT_GUID ; 
 int set_vf_node_guid (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_vf_port_guid (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5_ib_set_vf_guid(struct ib_device *device, int vf, u8 port,
			u64 guid, int type)
{
	if (type == IFLA_VF_IB_NODE_GUID)
		return set_vf_node_guid(device, vf, port, guid);
	else if (type == IFLA_VF_IB_PORT_GUID)
		return set_vf_port_guid(device, vf, port, guid);

	return -EINVAL;
}