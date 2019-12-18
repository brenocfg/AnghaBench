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
struct wmi_svc_avail_ev_arg {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_tlv_iter (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_svc_avail_ev_arg*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_svc_avail_parse ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_svc_avail(struct ath10k *ar,
					    struct sk_buff *skb,
					    struct wmi_svc_avail_ev_arg *arg)
{
	int ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_svc_avail_parse, arg);

	if (ret) {
		ath10k_warn(ar, "failed to parse svc_avail tlv: %d\n", ret);
		return ret;
	}

	return 0;
}