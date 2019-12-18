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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int device_cap_flags; } ;
struct ib_device {TYPE_1__ attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_DEVICE_ALLOW_USER_UNREG ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 int RDMA_NLDEV_ATTR_MAX ; 
 struct ib_device* ib_device_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  ib_unregister_device_and_put (struct ib_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nldev_policy ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nldev_dellink(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	struct ib_device *device;
	u32 index;
	int err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	if (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		return -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		return -EINVAL;

	if (!(device->attrs.device_cap_flags & IB_DEVICE_ALLOW_USER_UNREG)) {
		ib_device_put(device);
		return -EINVAL;
	}

	ib_unregister_device_and_put(device);
	return 0;
}