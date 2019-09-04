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
struct netlink_skb_parms {int dummy; } ;
struct cn_msg {int len; int /*<<< orphan*/  ack; int /*<<< orphan*/  seq; scalar_t__ data; } ;
typedef  enum proc_cn_mcast_op { ____Placeholder_proc_cn_mcast_op } proc_cn_mcast_op ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
#define  PROC_CN_MCAST_IGNORE 129 
#define  PROC_CN_MCAST_LISTEN 128 
 int /*<<< orphan*/  __netlink_ns_capable (struct netlink_skb_parms*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cn_proc_ack (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/ * current_user_ns () ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  proc_event_num_listeners ; 
 int /*<<< orphan*/ * task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn_proc_mcast_ctl(struct cn_msg *msg,
			      struct netlink_skb_parms *nsp)
{
	enum proc_cn_mcast_op *mc_op = NULL;
	int err = 0;

	if (msg->len != sizeof(*mc_op))
		return;

	/* 
	 * Events are reported with respect to the initial pid
	 * and user namespaces so ignore requestors from
	 * other namespaces.
	 */
	if ((current_user_ns() != &init_user_ns) ||
	    (task_active_pid_ns(current) != &init_pid_ns))
		return;

	/* Can only change if privileged. */
	if (!__netlink_ns_capable(nsp, &init_user_ns, CAP_NET_ADMIN)) {
		err = EPERM;
		goto out;
	}

	mc_op = (enum proc_cn_mcast_op *)msg->data;
	switch (*mc_op) {
	case PROC_CN_MCAST_LISTEN:
		atomic_inc(&proc_event_num_listeners);
		break;
	case PROC_CN_MCAST_IGNORE:
		atomic_dec(&proc_event_num_listeners);
		break;
	default:
		err = EINVAL;
		break;
	}

out:
	cn_proc_ack(err, msg->seq, msg->ack);
}