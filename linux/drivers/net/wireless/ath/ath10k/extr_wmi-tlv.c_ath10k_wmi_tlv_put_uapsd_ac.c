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
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct wmi_sta_uapsd_auto_trig_param {void* delay_interval; void* suspend_interval; void* service_interval; void* user_priority; void* wmm_ac; } ;
struct wmi_sta_uapsd_auto_trig_arg {int /*<<< orphan*/  delay_interval; int /*<<< orphan*/  suspend_interval; int /*<<< orphan*/  service_interval; int /*<<< orphan*/  user_priority; int /*<<< orphan*/  wmm_ac; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int WMI_TLV_TAG_STRUCT_STA_UAPSD_AUTO_TRIG_PARAM ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,void*,void*,void*,void*,void*) ; 

__attribute__((used)) static void *ath10k_wmi_tlv_put_uapsd_ac(struct ath10k *ar, void *ptr,
					 const struct wmi_sta_uapsd_auto_trig_arg *arg)
{
	struct wmi_sta_uapsd_auto_trig_param *ac;
	struct wmi_tlv *tlv;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_UAPSD_AUTO_TRIG_PARAM);
	tlv->len = __cpu_to_le16(sizeof(*ac));
	ac = (void *)tlv->value;

	ac->wmm_ac = __cpu_to_le32(arg->wmm_ac);
	ac->user_priority = __cpu_to_le32(arg->user_priority);
	ac->service_interval = __cpu_to_le32(arg->service_interval);
	ac->suspend_interval = __cpu_to_le32(arg->suspend_interval);
	ac->delay_interval = __cpu_to_le32(arg->delay_interval);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv vdev sta uapsd auto trigger ac %d prio %d svc int %d susp int %d delay int %d\n",
		   ac->wmm_ac, ac->user_priority, ac->service_interval,
		   ac->suspend_interval, ac->delay_interval);

	return ptr + sizeof(*tlv) + sizeof(*ac);
}