#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_client_nl_info {int port; TYPE_1__* cdev; int /*<<< orphan*/  abi; struct sk_buff* nl_msg; } ;
typedef  int /*<<< orphan*/  client_name ;
struct TYPE_5__ {int /*<<< orphan*/  portid; } ;
struct TYPE_4__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_CHARDEV ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_CHARDEV_ABI ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_CHARDEV_NAME ; 
 size_t RDMA_NLDEV_ATTR_CHARDEV_TYPE ; 
 int RDMA_NLDEV_ATTR_CHARDEV_TYPE_SIZE ; 
 size_t RDMA_NLDEV_ATTR_DEV_INDEX ; 
 int RDMA_NLDEV_ATTR_MAX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PAD ; 
 size_t RDMA_NLDEV_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_CMD_GET_CHARDEV ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NL_NLDEV ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  huge_encode_dev (int /*<<< orphan*/ ) ; 
 struct ib_device* ib_device_get_by_index (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int ib_get_client_nl_info (struct ib_device*,char*,struct ib_client_nl_info*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,struct nlattr*,int) ; 
 int /*<<< orphan*/  nldev_policy ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int) ; 
 int rdma_nl_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nldev_get_chardev(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	char client_name[RDMA_NLDEV_ATTR_CHARDEV_TYPE_SIZE];
	struct ib_client_nl_info data = {};
	struct ib_device *ibdev = NULL;
	struct sk_buff *msg;
	u32 index;
	int err;

	err = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1, nldev_policy,
			  extack);
	if (err || !tb[RDMA_NLDEV_ATTR_CHARDEV_TYPE])
		return -EINVAL;

	nla_strlcpy(client_name, tb[RDMA_NLDEV_ATTR_CHARDEV_TYPE],
		    sizeof(client_name));

	if (tb[RDMA_NLDEV_ATTR_DEV_INDEX]) {
		index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
		ibdev = ib_device_get_by_index(sock_net(skb->sk), index);
		if (!ibdev)
			return -EINVAL;

		if (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) {
			data.port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
			if (!rdma_is_port_valid(ibdev, data.port)) {
				err = -EINVAL;
				goto out_put;
			}
		} else {
			data.port = -1;
		}
	} else if (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) {
		return -EINVAL;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		err = -ENOMEM;
		goto out_put;
	}
	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_GET_CHARDEV),
			0, 0);

	data.nl_msg = msg;
	err = ib_get_client_nl_info(ibdev, client_name, &data);
	if (err)
		goto out_nlmsg;

	err = nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CHARDEV,
				huge_encode_dev(data.cdev->devt),
				RDMA_NLDEV_ATTR_PAD);
	if (err)
		goto out_data;
	err = nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CHARDEV_ABI, data.abi,
				RDMA_NLDEV_ATTR_PAD);
	if (err)
		goto out_data;
	if (nla_put_string(msg, RDMA_NLDEV_ATTR_CHARDEV_NAME,
			   dev_name(data.cdev))) {
		err = -EMSGSIZE;
		goto out_data;
	}

	nlmsg_end(msg, nlh);
	put_device(data.cdev);
	if (ibdev)
		ib_device_put(ibdev);
	return rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

out_data:
	put_device(data.cdev);
out_nlmsg:
	nlmsg_free(msg);
out_put:
	if (ibdev)
		ib_device_put(ibdev);
	return err;
}