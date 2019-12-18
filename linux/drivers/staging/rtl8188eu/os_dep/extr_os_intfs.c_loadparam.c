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
typedef  void* u8 ;
typedef  void* u16 ;
struct TYPE_2__ {int ssid_length; int /*<<< orphan*/  ssid; } ;
struct registry_priv {int accept_addba_req; int /*<<< orphan*/  monitor_enable; void* notch_filter; int /*<<< orphan*/  if2name; int /*<<< orphan*/  ifname; void* enable80211d; int /*<<< orphan*/  fw_iol; void* max_roaming_times; void* hwpdn_mode; void* antdiv_type; void* antdiv_cfg; void* channel_plan; void* wifi_spec; void* ampdu_amsdu; void* rx_stbc; void* ampdu_enable; void* cbw40_enable; void* ht_enable; void* uapsd_enable; void* wmm_enable; void* acm_method; scalar_t__ mp_mode; void* ips_mode; void* power_mgnt; void* smart_ps; void* preamble; void* frag_thresh; void* rts_thresh; void* vcs_type; void* vrtl_carrier_sense; void* wireless_mode; void* channel; TYPE_1__ ssid; } ;
struct net_device {int dummy; } ;
struct adapter {struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalDebugLevel ; 
 char* if2name ; 
 char* ifname ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ rtw_80211d ; 
 scalar_t__ rtw_acm_method ; 
 scalar_t__ rtw_ampdu_amsdu ; 
 scalar_t__ rtw_ampdu_enable ; 
 scalar_t__ rtw_antdiv_cfg ; 
 scalar_t__ rtw_antdiv_type ; 
 scalar_t__ rtw_cbw40_enable ; 
 scalar_t__ rtw_channel ; 
 scalar_t__ rtw_channel_plan ; 
 int /*<<< orphan*/  rtw_debug ; 
 scalar_t__ rtw_frag_thresh ; 
 int /*<<< orphan*/  rtw_fw_iol ; 
 scalar_t__ rtw_ht_enable ; 
 scalar_t__ rtw_hwpdn_mode ; 
 scalar_t__ rtw_ips_mode ; 
 scalar_t__ rtw_max_roaming_times ; 
 int /*<<< orphan*/  rtw_monitor_enable ; 
 scalar_t__ rtw_notch_filter ; 
 scalar_t__ rtw_power_mgnt ; 
 scalar_t__ rtw_preamble ; 
 scalar_t__ rtw_rts_thresh ; 
 scalar_t__ rtw_rx_stbc ; 
 scalar_t__ rtw_smart_ps ; 
 scalar_t__ rtw_uapsd_enable ; 
 scalar_t__ rtw_vcs_type ; 
 scalar_t__ rtw_vrtl_carrier_sense ; 
 scalar_t__ rtw_wifi_spec ; 
 scalar_t__ rtw_wireless_mode ; 
 scalar_t__ rtw_wmm_enable ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void loadparam(struct adapter *padapter, struct net_device *pnetdev)
{
	struct registry_priv *registry_par = &padapter->registrypriv;

	GlobalDebugLevel = rtw_debug;

	memcpy(registry_par->ssid.ssid, "ANY", 3);
	registry_par->ssid.ssid_length = 3;

	registry_par->channel = (u8)rtw_channel;
	registry_par->wireless_mode = (u8)rtw_wireless_mode;
	registry_par->vrtl_carrier_sense = (u8)rtw_vrtl_carrier_sense;
	registry_par->vcs_type = (u8)rtw_vcs_type;
	registry_par->rts_thresh = (u16)rtw_rts_thresh;
	registry_par->frag_thresh = (u16)rtw_frag_thresh;
	registry_par->preamble = (u8)rtw_preamble;
	registry_par->smart_ps =  (u8)rtw_smart_ps;
	registry_par->power_mgnt = (u8)rtw_power_mgnt;
	registry_par->ips_mode = (u8)rtw_ips_mode;
	registry_par->mp_mode = 0;
	registry_par->acm_method = (u8)rtw_acm_method;

	 /* UAPSD */
	registry_par->wmm_enable = (u8)rtw_wmm_enable;
	registry_par->uapsd_enable = (u8)rtw_uapsd_enable;

	registry_par->ht_enable = (u8)rtw_ht_enable;
	registry_par->cbw40_enable = (u8)rtw_cbw40_enable;
	registry_par->ampdu_enable = (u8)rtw_ampdu_enable;
	registry_par->rx_stbc = (u8)rtw_rx_stbc;
	registry_par->ampdu_amsdu = (u8)rtw_ampdu_amsdu;
	registry_par->wifi_spec = (u8)rtw_wifi_spec;
	registry_par->channel_plan = (u8)rtw_channel_plan;
	registry_par->accept_addba_req = true;
	registry_par->antdiv_cfg = (u8)rtw_antdiv_cfg;
	registry_par->antdiv_type = (u8)rtw_antdiv_type;
	registry_par->hwpdn_mode = (u8)rtw_hwpdn_mode;

	registry_par->max_roaming_times = (u8)rtw_max_roaming_times;

	registry_par->fw_iol = rtw_fw_iol;

	registry_par->enable80211d = (u8)rtw_80211d;
	snprintf(registry_par->ifname, 16, "%s", ifname);
	snprintf(registry_par->if2name, 16, "%s", if2name);
	registry_par->notch_filter = (u8)rtw_notch_filter;
	registry_par->monitor_enable = rtw_monitor_enable;
}