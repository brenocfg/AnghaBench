#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct ib_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 int RDMA_NLDEV_ATTR_MAX ; 
 int /*<<< orphan*/  RDMA_NLDEV_CMD_PORT_GET ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NL_NLDEV ; 
 scalar_t__ fill_port_info (struct sk_buff*,struct ib_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ib_device* ib_device_get_by_index (scalar_t__) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nldev_policy ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int nlmsg_parse (TYPE_1__*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_end_port (struct ib_device*) ; 
 scalar_t__ rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nldev_port_get_dumpit(struct sk_buff *skb,
				 struct netlink_callback *cb)
{
	struct nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	struct ib_device *device;
	int start = cb->args[0];
	struct nlmsghdr *nlh;
	u32 idx = 0;
	u32 ifindex;
	int err;
	u32 p;

	err = nlmsg_parse(cb->nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, NULL);
	if (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		return -EINVAL;

	ifindex = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(ifindex);
	if (!device)
		return -EINVAL;

	for (p = rdma_start_port(device); p <= rdma_end_port(device); ++p) {
		/*
		 * The dumpit function returns all information from specific
		 * index. This specific index is taken from the netlink
		 * messages request sent by user and it is available
		 * in cb->args[0].
		 *
		 * Usually, the user doesn't fill this field and it causes
		 * to return everything.
		 *
		 */
		if (idx < start) {
			idx++;
			continue;
		}

		nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq,
				RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
						 RDMA_NLDEV_CMD_PORT_GET),
				0, NLM_F_MULTI);

		if (fill_port_info(skb, device, p, sock_net(skb->sk))) {
			nlmsg_cancel(skb, nlh);
			goto out;
		}
		idx++;
		nlmsg_end(skb, nlh);
	}

out:
	put_device(&device->dev);
	cb->args[0] = idx;
	return skb->len;
}