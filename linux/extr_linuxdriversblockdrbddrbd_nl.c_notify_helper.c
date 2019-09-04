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
struct drbd_resource {int dummy; } ;
struct drbd_helper_info {int helper_status; int /*<<< orphan*/  helper_name_len; int /*<<< orphan*/  helper_name; } ;
struct drbd_genlmsghdr {int minor; int /*<<< orphan*/  ret_code; } ;
struct drbd_device {int minor; struct drbd_resource* resource; } ;
struct drbd_connection {struct drbd_resource* resource; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_HELPER ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  NO_ERROR ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_resource*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  drbd_genl_family ; 
 int drbd_genl_multicast_events (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ drbd_helper_info_to_skb (struct sk_buff*,struct drbd_helper_info*,int) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct drbd_genlmsghdr*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drbd_genlmsghdr* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_drbd_cfg_context (struct sk_buff*,struct drbd_resource*,struct drbd_connection*,struct drbd_device*) ; 
 scalar_t__ nla_put_notification_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  notification_mutex ; 
 int /*<<< orphan*/  notify_genl_seq ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void notify_helper(enum drbd_notification_type type,
		   struct drbd_device *device, struct drbd_connection *connection,
		   const char *name, int status)
{
	struct drbd_resource *resource = device ? device->resource : connection->resource;
	struct drbd_helper_info helper_info;
	unsigned int seq = atomic_inc_return(&notify_genl_seq);
	struct sk_buff *skb = NULL;
	struct drbd_genlmsghdr *dh;
	int err;

	strlcpy(helper_info.helper_name, name, sizeof(helper_info.helper_name));
	helper_info.helper_name_len = min(strlen(name), sizeof(helper_info.helper_name));
	helper_info.helper_status = status;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
	err = -ENOMEM;
	if (!skb)
		goto fail;

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_HELPER);
	if (!dh)
		goto fail;
	dh->minor = device ? device->minor : -1;
	dh->ret_code = NO_ERROR;
	mutex_lock(&notification_mutex);
	if (nla_put_drbd_cfg_context(skb, resource, connection, device) ||
	    nla_put_notification_header(skb, type) ||
	    drbd_helper_info_to_skb(skb, &helper_info, true))
		goto unlock_fail;
	genlmsg_end(skb, dh);
	err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
	skb = NULL;
	/* skb has been consumed or freed in netlink_broadcast() */
	if (err && err != -ESRCH)
		goto unlock_fail;
	mutex_unlock(&notification_mutex);
	return;

unlock_fail:
	mutex_unlock(&notification_mutex);
fail:
	nlmsg_free(skb);
	drbd_err(resource, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
}