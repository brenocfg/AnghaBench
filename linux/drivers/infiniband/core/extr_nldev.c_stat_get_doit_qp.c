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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_nl_counter_mode { ____Placeholder_rdma_nl_counter_mode } rdma_nl_counter_mode ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int RDMA_COUNTER_MODE_AUTO ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 size_t RDMA_NLDEV_ATTR_PORT_INDEX ; 
 size_t RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK ; 
 size_t RDMA_NLDEV_ATTR_STAT_COUNTER_ID ; 
 size_t RDMA_NLDEV_ATTR_STAT_MODE ; 
 int /*<<< orphan*/  RDMA_NLDEV_CMD_STAT_GET ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NL_NLDEV ; 
 scalar_t__ fill_nldev_handle (struct sk_buff*,struct ib_device*) ; 
 struct ib_device* ib_device_get_by_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,size_t,int) ; 
 int nldev_res_get_counter_doit (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_counter_get_mode (struct ib_device*,int,int*,int*) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int) ; 
 int rdma_nl_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stat_get_doit_qp(struct sk_buff *skb, struct nlmsghdr *nlh,
			    struct netlink_ext_ack *extack, struct nlattr *tb[])

{
	static enum rdma_nl_counter_mode mode;
	static enum rdma_nl_counter_mask mask;
	struct ib_device *device;
	struct sk_buff *msg;
	u32 index, port;
	int ret;

	if (tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID])
		return nldev_res_get_counter_doit(skb, nlh, extack);

	if (!tb[RDMA_NLDEV_ATTR_STAT_MODE] ||
	    !tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !tb[RDMA_NLDEV_ATTR_PORT_INDEX])
		return -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		return -EINVAL;

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	if (!rdma_is_port_valid(device, port)) {
		ret = -EINVAL;
		goto err;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto err;
	}

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_STAT_GET),
			0, 0);

	ret = rdma_counter_get_mode(device, port, &mode, &mask);
	if (ret)
		goto err_msg;

	if (fill_nldev_handle(msg, device) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_MODE, mode)) {
		ret = -EMSGSIZE;
		goto err_msg;
	}

	if ((mode == RDMA_COUNTER_MODE_AUTO) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK, mask)) {
		ret = -EMSGSIZE;
		goto err_msg;
	}

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	return rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_msg:
	nlmsg_free(msg);
err:
	ib_device_put(device);
	return ret;
}