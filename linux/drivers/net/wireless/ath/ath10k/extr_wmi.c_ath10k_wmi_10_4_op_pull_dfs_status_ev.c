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
struct wmi_dfs_status_ev_arg {int /*<<< orphan*/  status; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 

__attribute__((used)) static int
ath10k_wmi_10_4_op_pull_dfs_status_ev(struct ath10k *ar, struct sk_buff *skb,
				      struct wmi_dfs_status_ev_arg *arg)
{
	struct wmi_dfs_status_ev_arg *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	arg->status = ev->status;

	return 0;
}