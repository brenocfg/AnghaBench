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
struct wmi_start_scan_cmd {int /*<<< orphan*/  burst_duration_ms; int /*<<< orphan*/  tlvs; int /*<<< orphan*/  common; } ;
struct wmi_start_scan_arg {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_wmi_put_start_scan_common (int /*<<< orphan*/ *,struct wmi_start_scan_arg const*) ; 
 int /*<<< orphan*/  ath10k_wmi_put_start_scan_tlvs (int /*<<< orphan*/ *,struct wmi_start_scan_arg const*) ; 
 int ath10k_wmi_start_scan_tlvs_len (struct wmi_start_scan_arg const*) ; 
 int ath10k_wmi_start_scan_verify (struct wmi_start_scan_arg const*) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_start_scan(struct ath10k *ar,
			     const struct wmi_start_scan_arg *arg)
{
	struct wmi_start_scan_cmd *cmd;
	struct sk_buff *skb;
	size_t len;
	int ret;

	ret = ath10k_wmi_start_scan_verify(arg);
	if (ret)
		return ERR_PTR(ret);

	len = sizeof(*cmd) + ath10k_wmi_start_scan_tlvs_len(arg);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_start_scan_cmd *)skb->data;

	ath10k_wmi_put_start_scan_common(&cmd->common, arg);
	ath10k_wmi_put_start_scan_tlvs(&cmd->tlvs, arg);

	cmd->burst_duration_ms = __cpu_to_le32(0);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi start scan\n");
	return skb;
}