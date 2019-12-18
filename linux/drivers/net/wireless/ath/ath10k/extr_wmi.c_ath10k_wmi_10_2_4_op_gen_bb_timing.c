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
struct wmi_pdev_bb_timing_cfg_cmd {void* bb_xpa_timing; void* bb_tx_timing; } ;
struct wmi_bb_timing_cfg_arg {int /*<<< orphan*/  bb_xpa_timing; int /*<<< orphan*/  bb_tx_timing; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_10_2_4_op_gen_bb_timing(struct ath10k *ar,
				   const struct wmi_bb_timing_cfg_arg *arg)
{
	struct wmi_pdev_bb_timing_cfg_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_pdev_bb_timing_cfg_cmd *)skb->data;
	cmd->bb_tx_timing = __cpu_to_le32(arg->bb_tx_timing);
	cmd->bb_xpa_timing = __cpu_to_le32(arg->bb_xpa_timing);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev bb_tx_timing 0x%x bb_xpa_timing 0x%x\n",
		   arg->bb_tx_timing, arg->bb_xpa_timing);
	return skb;
}