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
typedef  int u32 ;
struct wmi_force_fw_hang_cmd {void* delay_ms; void* type; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_force_fw_hang_type { ____Placeholder_wmi_force_fw_hang_type } wmi_force_fw_hang_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_force_fw_hang(struct ath10k *ar,
				enum wmi_force_fw_hang_type type, u32 delay_ms)
{
	struct wmi_force_fw_hang_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_force_fw_hang_cmd *)skb->data;
	cmd->type = __cpu_to_le32(type);
	cmd->delay_ms = __cpu_to_le32(delay_ms);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi force fw hang %d delay %d\n",
		   type, delay_ms);
	return skb;
}