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
struct drbd_genlmsghdr {unsigned int minor; int /*<<< orphan*/  ret_code; } ;
struct drbd_connection {int /*<<< orphan*/  flags; int /*<<< orphan*/  resource; } ;
struct connection_statistics {int /*<<< orphan*/  conn_congested; } ;
struct connection_info {int dummy; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DRBD_CONNECTION_STATE ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  NET_CONGESTED ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NOTIFY_DESTROY ; 
 int NOTIFY_FLAGS ; 
 int /*<<< orphan*/  NO_ERROR ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ connection_info_to_skb (struct sk_buff*,struct connection_info*,int) ; 
 int /*<<< orphan*/  connection_statistics_to_skb (struct sk_buff*,struct connection_statistics*,int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  drbd_genl_family ; 
 int drbd_genl_multicast_events (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct drbd_genlmsghdr*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drbd_genlmsghdr* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_drbd_cfg_context (struct sk_buff*,int /*<<< orphan*/ ,struct drbd_connection*,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_notification_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  notify_genl_seq ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void notify_connection_state(struct sk_buff *skb,
			     unsigned int seq,
			     struct drbd_connection *connection,
			     struct connection_info *connection_info,
			     enum drbd_notification_type type)
{
	struct connection_statistics connection_statistics;
	struct drbd_genlmsghdr *dh;
	bool multicast = false;
	int err;

	if (!skb) {
		seq = atomic_inc_return(&notify_genl_seq);
		skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
		err = -ENOMEM;
		if (!skb)
			goto failed;
		multicast = true;
	}

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_CONNECTION_STATE);
	if (!dh)
		goto nla_put_failure;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	if (nla_put_drbd_cfg_context(skb, connection->resource, connection, NULL) ||
	    nla_put_notification_header(skb, type) ||
	    ((type & ~NOTIFY_FLAGS) != NOTIFY_DESTROY &&
	     connection_info_to_skb(skb, connection_info, true)))
		goto nla_put_failure;
	connection_statistics.conn_congested = test_bit(NET_CONGESTED, &connection->flags);
	connection_statistics_to_skb(skb, &connection_statistics, !capable(CAP_SYS_ADMIN));
	genlmsg_end(skb, dh);
	if (multicast) {
		err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
		/* skb has been consumed or freed in netlink_broadcast() */
		if (err && err != -ESRCH)
			goto failed;
	}
	return;

nla_put_failure:
	nlmsg_free(skb);
failed:
	drbd_err(connection, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
}