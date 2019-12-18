#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_peer_sta_kickout_event {TYPE_1__ peer_macaddr; } ;
struct wmi_peer_kick_ev_arg {int /*<<< orphan*/  mac_addr; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int
ath10k_wmi_op_pull_peer_kick_ev(struct ath10k *ar, struct sk_buff *skb,
				struct wmi_peer_kick_ev_arg *arg)
{
	struct wmi_peer_sta_kickout_event *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	skb_pull(skb, sizeof(*ev));
	arg->mac_addr = ev->peer_macaddr.addr;

	return 0;
}