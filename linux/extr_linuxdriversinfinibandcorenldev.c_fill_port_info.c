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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct ib_port_attr {int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; int /*<<< orphan*/  subnet_prefix; scalar_t__ port_cap_flags; } ;
struct ib_device {struct net_device* (* get_netdev ) (struct ib_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_CAP_FLAGS ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_LID ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_LMC ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_NDEV_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_NDEV_NAME ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PAD ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PORT_PHYS_STATE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PORT_STATE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_SM_LID ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_SUBNET_PREFIX ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 scalar_t__ fill_nldev_handle (struct sk_buff*,struct ib_device*) ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net const*) ; 
 int nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 
 struct net_device* stub1 (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_port_info(struct sk_buff *msg,
			  struct ib_device *device, u32 port,
			  const struct net *net)
{
	struct net_device *netdev = NULL;
	struct ib_port_attr attr;
	int ret;

	if (fill_nldev_handle(msg, device))
		return -EMSGSIZE;

	if (nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port))
		return -EMSGSIZE;

	ret = ib_query_port(device, port, &attr);
	if (ret)
		return ret;

	if (rdma_protocol_ib(device, port)) {
		BUILD_BUG_ON(sizeof(attr.port_cap_flags) > sizeof(u64));
		if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CAP_FLAGS,
				      (u64)attr.port_cap_flags,
				      RDMA_NLDEV_ATTR_PAD))
			return -EMSGSIZE;
		if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_SUBNET_PREFIX,
				      attr.subnet_prefix, RDMA_NLDEV_ATTR_PAD))
			return -EMSGSIZE;
		if (nla_put_u32(msg, RDMA_NLDEV_ATTR_LID, attr.lid))
			return -EMSGSIZE;
		if (nla_put_u32(msg, RDMA_NLDEV_ATTR_SM_LID, attr.sm_lid))
			return -EMSGSIZE;
		if (nla_put_u8(msg, RDMA_NLDEV_ATTR_LMC, attr.lmc))
			return -EMSGSIZE;
	}
	if (nla_put_u8(msg, RDMA_NLDEV_ATTR_PORT_STATE, attr.state))
		return -EMSGSIZE;
	if (nla_put_u8(msg, RDMA_NLDEV_ATTR_PORT_PHYS_STATE, attr.phys_state))
		return -EMSGSIZE;

	if (device->get_netdev)
		netdev = device->get_netdev(device, port);

	if (netdev && net_eq(dev_net(netdev), net)) {
		ret = nla_put_u32(msg,
				  RDMA_NLDEV_ATTR_NDEV_INDEX, netdev->ifindex);
		if (ret)
			goto out;
		ret = nla_put_string(msg,
				     RDMA_NLDEV_ATTR_NDEV_NAME, netdev->name);
	}

out:
	if (netdev)
		dev_put(netdev);
	return ret;
}