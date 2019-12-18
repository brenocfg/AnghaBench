#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rdma_hw_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/ * names; scalar_t__* value; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_5__ {int (* get_hw_stats ) (struct ib_device*,struct rdma_hw_stats*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  alloc_hw_stats; } ;
struct ib_device {TYPE_2__ ops; TYPE_1__* port_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_4__ {struct rdma_hw_stats* hw_stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 size_t RDMA_NLDEV_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_STAT_HWCOUNTERS ; 
 int /*<<< orphan*/  RDMA_NLDEV_CMD_STAT_GET ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NL_NLDEV ; 
 scalar_t__ fill_nldev_handle (struct sk_buff*,struct ib_device*) ; 
 scalar_t__ fill_stat_hwcounter_entry (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ib_device* ib_device_get_by_index (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,size_t,size_t) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_counter_get_hwstat_value (struct ib_device*,size_t,int) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,size_t) ; 
 int rdma_nl_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,struct rdma_hw_stats*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stat_get_doit_default_counter(struct sk_buff *skb,
					 struct nlmsghdr *nlh,
					 struct netlink_ext_ack *extack,
					 struct nlattr *tb[])
{
	struct rdma_hw_stats *stats;
	struct nlattr *table_attr;
	struct ib_device *device;
	int ret, num_cnts, i;
	struct sk_buff *msg;
	u32 index, port;
	u64 v;

	if (!tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !tb[RDMA_NLDEV_ATTR_PORT_INDEX])
		return -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		return -EINVAL;

	if (!device->ops.alloc_hw_stats || !device->ops.get_hw_stats) {
		ret = -EINVAL;
		goto err;
	}

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

	if (fill_nldev_handle(msg, device) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port)) {
		ret = -EMSGSIZE;
		goto err_msg;
	}

	stats = device->port_data ? device->port_data[port].hw_stats : NULL;
	if (stats == NULL) {
		ret = -EINVAL;
		goto err_msg;
	}
	mutex_lock(&stats->lock);

	num_cnts = device->ops.get_hw_stats(device, stats, port, 0);
	if (num_cnts < 0) {
		ret = -EINVAL;
		goto err_stats;
	}

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTERS);
	if (!table_attr) {
		ret = -EMSGSIZE;
		goto err_stats;
	}
	for (i = 0; i < num_cnts; i++) {
		v = stats->value[i] +
			rdma_counter_get_hwstat_value(device, port, i);
		if (fill_stat_hwcounter_entry(msg, stats->names[i], v)) {
			ret = -EMSGSIZE;
			goto err_table;
		}
	}
	nla_nest_end(msg, table_attr);

	mutex_unlock(&stats->lock);
	nlmsg_end(msg, nlh);
	ib_device_put(device);
	return rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_table:
	nla_nest_cancel(msg, table_attr);
err_stats:
	mutex_unlock(&stats->lock);
err_msg:
	nlmsg_free(msg);
err:
	ib_device_put(device);
	return ret;
}