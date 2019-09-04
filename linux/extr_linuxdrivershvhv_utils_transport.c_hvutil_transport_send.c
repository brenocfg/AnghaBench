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
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;
struct hvutil_transport {scalar_t__ mode; int outmsg_len; void (* on_read ) () ;int /*<<< orphan*/  lock; int /*<<< orphan*/  outmsg_q; void* outmsg; TYPE_2__ cn_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;
struct cn_msg {int len; void* data; TYPE_1__ id; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HVUTIL_TRANSPORT_CHARDEV ; 
 scalar_t__ HVUTIL_TRANSPORT_DESTROY ; 
 scalar_t__ HVUTIL_TRANSPORT_INIT ; 
 scalar_t__ HVUTIL_TRANSPORT_NETLINK ; 
 int cn_netlink_send (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cn_msg*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int hvutil_transport_send(struct hvutil_transport *hvt, void *msg, int len,
			  void (*on_read_cb)(void))
{
	struct cn_msg *cn_msg;
	int ret = 0;

	if (hvt->mode == HVUTIL_TRANSPORT_INIT ||
	    hvt->mode == HVUTIL_TRANSPORT_DESTROY) {
		return -EINVAL;
	} else if (hvt->mode == HVUTIL_TRANSPORT_NETLINK) {
		cn_msg = kzalloc(sizeof(*cn_msg) + len, GFP_ATOMIC);
		if (!cn_msg)
			return -ENOMEM;
		cn_msg->id.idx = hvt->cn_id.idx;
		cn_msg->id.val = hvt->cn_id.val;
		cn_msg->len = len;
		memcpy(cn_msg->data, msg, len);
		ret = cn_netlink_send(cn_msg, 0, 0, GFP_ATOMIC);
		kfree(cn_msg);
		/*
		 * We don't know when netlink messages are delivered but unlike
		 * in CHARDEV mode we're not blocked and we can send next
		 * messages right away.
		 */
		if (on_read_cb)
			on_read_cb();
		return ret;
	}
	/* HVUTIL_TRANSPORT_CHARDEV */
	mutex_lock(&hvt->lock);
	if (hvt->mode != HVUTIL_TRANSPORT_CHARDEV) {
		ret = -EINVAL;
		goto out_unlock;
	}

	if (hvt->outmsg) {
		/* Previous message wasn't received */
		ret = -EFAULT;
		goto out_unlock;
	}
	hvt->outmsg = kzalloc(len, GFP_KERNEL);
	if (hvt->outmsg) {
		memcpy(hvt->outmsg, msg, len);
		hvt->outmsg_len = len;
		hvt->on_read = on_read_cb;
		wake_up_interruptible(&hvt->outmsg_q);
	} else
		ret = -ENOMEM;
out_unlock:
	mutex_unlock(&hvt->lock);
	return ret;
}