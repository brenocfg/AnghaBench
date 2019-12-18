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
struct wmi_rdy_ev_arg {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  status; int /*<<< orphan*/  abi_version; int /*<<< orphan*/  sw_version; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unified_ready; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_pull_rdy (struct ath10k*,struct sk_buff*,struct wmi_rdy_ev_arg*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 

int ath10k_wmi_event_ready(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_rdy_ev_arg arg = {};
	int ret;

	ret = ath10k_wmi_pull_rdy(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse ready event: %d\n", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event ready sw_version %u abi_version %u mac_addr %pM status %d\n",
		   __le32_to_cpu(arg.sw_version),
		   __le32_to_cpu(arg.abi_version),
		   arg.mac_addr,
		   __le32_to_cpu(arg.status));

	if (is_zero_ether_addr(ar->mac_addr))
		ether_addr_copy(ar->mac_addr, arg.mac_addr);
	complete(&ar->wmi.unified_ready);
	return 0;
}