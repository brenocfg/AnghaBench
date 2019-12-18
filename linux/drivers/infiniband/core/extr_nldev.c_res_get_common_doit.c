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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rdma_restrack_entry {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nldev_fill_res_entry {size_t id; int flags; int (* fill_res_func ) (struct sk_buff*,int,struct rdma_restrack_entry*,scalar_t__) ;int /*<<< orphan*/  nldev_cmd; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_restrack_type { ____Placeholder_rdma_restrack_type } rdma_restrack_type ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rdma_restrack_entry*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLDEV_PER_DEV ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (struct rdma_restrack_entry*) ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 int RDMA_NLDEV_ATTR_MAX ; 
 size_t RDMA_NLDEV_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NL_NLDEV ; 
 struct nldev_fill_res_entry* fill_entries ; 
 scalar_t__ fill_nldev_handle (struct sk_buff*,struct ib_device*) ; 
 struct ib_device* ib_device_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int netlink_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nldev_policy ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,scalar_t__) ; 
 int /*<<< orphan*/  rdma_is_visible_in_pid_ns (struct rdma_restrack_entry*) ; 
 int rdma_nl_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct rdma_restrack_entry* rdma_restrack_get_byid (struct ib_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  rdma_restrack_put (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,int,struct rdma_restrack_entry*,scalar_t__) ; 

__attribute__((used)) static int res_get_common_doit(struct sk_buff *skb, struct nlmsghdr *nlh,
			       struct netlink_ext_ack *extack,
			       enum rdma_restrack_type res_type)
{
	const struct nldev_fill_res_entry *fe = &fill_entries[res_type];
	struct nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	struct rdma_restrack_entry *res;
	struct ib_device *device;
	u32 index, id, port = 0;
	bool has_cap_net_admin;
	struct sk_buff *msg;
	int ret;

	ret = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	if (ret || !tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !fe->id || !tb[fe->id])
		return -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		return -EINVAL;

	if (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) {
		port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
		if (!rdma_is_port_valid(device, port)) {
			ret = -EINVAL;
			goto err;
		}
	}

	if ((port && fe->flags & NLDEV_PER_DEV) ||
	    (!port && ~fe->flags & NLDEV_PER_DEV)) {
		ret = -EINVAL;
		goto err;
	}

	id = nla_get_u32(tb[fe->id]);
	res = rdma_restrack_get_byid(device, res_type, id);
	if (IS_ERR(res)) {
		ret = PTR_ERR(res);
		goto err;
	}

	if (!rdma_is_visible_in_pid_ns(res)) {
		ret = -ENOENT;
		goto err_get;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto err_get;
	}

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, fe->nldev_cmd),
			0, 0);

	if (fill_nldev_handle(msg, device)) {
		ret = -EMSGSIZE;
		goto err_free;
	}

	has_cap_net_admin = netlink_capable(skb, CAP_NET_ADMIN);
	ret = fe->fill_res_func(msg, has_cap_net_admin, res, port);
	rdma_restrack_put(res);
	if (ret)
		goto err_free;

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	return rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_free:
	nlmsg_free(msg);
err_get:
	rdma_restrack_put(res);
err:
	ib_device_put(device);
	return ret;
}