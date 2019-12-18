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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RDMA_NLDEV_ATTR_MAX ; 
#define  RDMA_NLDEV_ATTR_RES_QP 128 
 size_t RDMA_NLDEV_ATTR_STAT_RES ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nldev_policy ; 
 int nlmsg_parse (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int stat_get_doit_default_counter (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*,struct nlattr**) ; 
 int stat_get_doit_qp (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*,struct nlattr**) ; 

__attribute__((used)) static int nldev_stat_get_doit(struct sk_buff *skb, struct nlmsghdr *nlh,
			       struct netlink_ext_ack *extack)
{
	struct nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	int ret;

	ret = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	if (ret)
		return -EINVAL;

	if (!tb[RDMA_NLDEV_ATTR_STAT_RES])
		return stat_get_doit_default_counter(skb, nlh, extack, tb);

	switch (nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_RES])) {
	case RDMA_NLDEV_ATTR_RES_QP:
		ret = stat_get_doit_qp(skb, nlh, extack, tb);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}