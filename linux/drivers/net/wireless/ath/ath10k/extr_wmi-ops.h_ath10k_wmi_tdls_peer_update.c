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
struct wmi_tdls_peer_update_cmd_arg {int dummy; } ;
struct wmi_tdls_peer_capab_arg {int dummy; } ;
struct wmi_channel_arg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct ath10k {TYPE_3__ wmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  tdls_peer_update_cmdid; } ;
struct TYPE_4__ {struct sk_buff* (* gen_tdls_peer_update ) (struct ath10k*,struct wmi_tdls_peer_update_cmd_arg const*,struct wmi_tdls_peer_capab_arg const*,struct wmi_channel_arg const*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,struct wmi_tdls_peer_update_cmd_arg const*,struct wmi_tdls_peer_capab_arg const*,struct wmi_channel_arg const*) ; 

__attribute__((used)) static inline int
ath10k_wmi_tdls_peer_update(struct ath10k *ar,
			    const struct wmi_tdls_peer_update_cmd_arg *arg,
			    const struct wmi_tdls_peer_capab_arg *cap,
			    const struct wmi_channel_arg *chan)
{
	struct sk_buff *skb;

	if (!ar->wmi.ops->gen_tdls_peer_update)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_tdls_peer_update(ar, arg, cap, chan);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	return ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->tdls_peer_update_cmdid);
}