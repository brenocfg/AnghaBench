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
struct wmi_svc_avail_ev_arg {int /*<<< orphan*/  service_map_ext_len; int /*<<< orphan*/  service_map_ext; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_map_svc_ext (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_pull_svc_avail (struct ath10k*,struct sk_buff*,struct wmi_svc_avail_ev_arg*) ; 

void ath10k_wmi_event_service_available(struct ath10k *ar, struct sk_buff *skb)
{
	int ret;
	struct wmi_svc_avail_ev_arg arg = {};

	ret = ath10k_wmi_pull_svc_avail(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse service available event: %d\n",
			    ret);
	}

	ath10k_wmi_map_svc_ext(ar, arg.service_map_ext, ar->wmi.svc_map,
			       __le32_to_cpu(arg.service_map_ext_len));
}