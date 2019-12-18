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
struct wmi_vdev_start_request_arg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct ath10k {TYPE_3__ wmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_restart_request_cmdid; } ;
struct TYPE_4__ {struct sk_buff* (* gen_vdev_start ) (struct ath10k*,struct wmi_vdev_start_request_arg const*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,struct wmi_vdev_start_request_arg const*,int) ; 

__attribute__((used)) static inline int
ath10k_wmi_vdev_restart(struct ath10k *ar,
			const struct wmi_vdev_start_request_arg *arg)
{
	struct sk_buff *skb;

	if (!ar->wmi.ops->gen_vdev_start)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_start(ar, arg, true);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	return ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->vdev_restart_request_cmdid);
}