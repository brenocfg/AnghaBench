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
struct wmi_echo_event {int /*<<< orphan*/  value; } ;
struct wmi_echo_ev_arg {int /*<<< orphan*/  value; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ath10k_wmi_op_pull_echo_ev(struct ath10k *ar,
				      struct sk_buff *skb,
				      struct wmi_echo_ev_arg *arg)
{
	struct wmi_echo_event *ev = (void *)skb->data;

	arg->value = ev->value;

	return 0;
}