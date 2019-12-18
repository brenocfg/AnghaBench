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
typedef  int u32 ;
struct wmi_ext_resource_config_10_4_cmd {void* max_tdls_concurrent_buffer_sta; void* max_tdls_concurrent_sleep_sta; void* num_tdls_conn_table_entries; void* num_tdls_vdevs; void* coex_gpio_pin3; void* coex_gpio_pin2; void* coex_gpio_pin1; void* coex_version; void* wlan_gpio_priority; void* fw_feature_bitmap; void* host_platform_config; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; } ;
typedef  enum wmi_host_platform_type { ____Placeholder_wmi_host_platform_type } wmi_host_platform_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int TARGET_10_4_NUM_TDLS_BUFFER_STA ; 
 int TARGET_10_4_NUM_TDLS_SLEEP_STA ; 
 int TARGET_10_4_NUM_TDLS_VDEVS ; 
 int WMI_NO_COEX_VERSION_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_TDLS_UAPSD_SLEEP_STA ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_10_4_ext_resource_config(struct ath10k *ar,
				    enum wmi_host_platform_type type,
				    u32 fw_feature_bitmap)
{
	struct wmi_ext_resource_config_10_4_cmd *cmd;
	struct sk_buff *skb;
	u32 num_tdls_sleep_sta = 0;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	if (test_bit(WMI_SERVICE_TDLS_UAPSD_SLEEP_STA, ar->wmi.svc_map))
		num_tdls_sleep_sta = TARGET_10_4_NUM_TDLS_SLEEP_STA;

	cmd = (struct wmi_ext_resource_config_10_4_cmd *)skb->data;
	cmd->host_platform_config = __cpu_to_le32(type);
	cmd->fw_feature_bitmap = __cpu_to_le32(fw_feature_bitmap);
	cmd->wlan_gpio_priority = __cpu_to_le32(-1);
	cmd->coex_version = __cpu_to_le32(WMI_NO_COEX_VERSION_SUPPORT);
	cmd->coex_gpio_pin1 = __cpu_to_le32(-1);
	cmd->coex_gpio_pin2 = __cpu_to_le32(-1);
	cmd->coex_gpio_pin3 = __cpu_to_le32(-1);
	cmd->num_tdls_vdevs = __cpu_to_le32(TARGET_10_4_NUM_TDLS_VDEVS);
	cmd->num_tdls_conn_table_entries = __cpu_to_le32(20);
	cmd->max_tdls_concurrent_sleep_sta = __cpu_to_le32(num_tdls_sleep_sta);
	cmd->max_tdls_concurrent_buffer_sta =
			__cpu_to_le32(TARGET_10_4_NUM_TDLS_BUFFER_STA);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi ext resource config host type %d firmware feature bitmap %08x\n",
		   type, fw_feature_bitmap);
	return skb;
}