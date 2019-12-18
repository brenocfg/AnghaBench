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
struct wmi_cmd_hdr {int dummy; } ;
struct wmi {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int ath6kl_wmi_proc_events (struct wmi*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_ath6kl_wmi_event (int /*<<< orphan*/ ,int) ; 

int ath6kl_wmi_control_rx(struct wmi *wmi, struct sk_buff *skb)
{
	if (WARN_ON(skb == NULL))
		return -EINVAL;

	if (skb->len < sizeof(struct wmi_cmd_hdr)) {
		ath6kl_err("bad packet 1\n");
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	trace_ath6kl_wmi_event(skb->data, skb->len);

	return ath6kl_wmi_proc_events(wmi, skb);
}