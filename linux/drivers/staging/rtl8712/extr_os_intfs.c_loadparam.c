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
struct TYPE_2__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
struct registry_priv {void* wifi_test; void* low_power; void* rf_config; void* ampdu_enable; void* cbw40_enable; void* ht_enable; void* uapsd_acvo_en; void* uapsd_acvi_en; void* uapsd_acbe_en; void* uapsd_acbk_en; void* uapsd_max_sp; void* uapsd_enable; void* wmm_enable; void* software_decrypt; void* software_encrypt; void* mp_mode; void* ack_policy; void* busy_thresh; void* short_retry_lmt; void* long_retry_lmt; void* radio_enable; void* power_mgnt; void* smart_ps; void* soft_ap; void* adhoc_tx_pwr; void* scan_mode; void* preamble; void* frag_thresh; void* vcs_type; void* vrtl_carrier_sense; void* wireless_mode; void* channel; TYPE_1__ ssid; void* network_mode; void* hci; void* lbkmode; void* rfintfs; void* chip_version; } ;
struct net_device {int dummy; } ;
struct _adapter {struct registry_priv registrypriv; } ;

/* Variables and functions */
 scalar_t__ ack_policy ; 
 scalar_t__ adhoc_tx_pwr ; 
 scalar_t__ ampdu_enable ; 
 scalar_t__ busy_thresh ; 
 scalar_t__ cbw40_enable ; 
 scalar_t__ channel ; 
 scalar_t__ chip_version ; 
 scalar_t__ frag_thresh ; 
 scalar_t__ hci ; 
 scalar_t__ ht_enable ; 
 int /*<<< orphan*/  initmac ; 
 scalar_t__ lbkmode ; 
 scalar_t__ long_retry_lmt ; 
 scalar_t__ low_power ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mp_mode ; 
 scalar_t__ network_mode ; 
 scalar_t__ power_mgnt ; 
 scalar_t__ preamble ; 
 int /*<<< orphan*/  r8712_initmac ; 
 scalar_t__ radio_enable ; 
 scalar_t__ rf_config ; 
 scalar_t__ rfintfs ; 
 scalar_t__ scan_mode ; 
 scalar_t__ short_retry_lmt ; 
 scalar_t__ smart_ps ; 
 scalar_t__ soft_ap ; 
 scalar_t__ software_decrypt ; 
 scalar_t__ software_encrypt ; 
 scalar_t__ uapsd_acbe_en ; 
 scalar_t__ uapsd_acbk_en ; 
 scalar_t__ uapsd_acvi_en ; 
 scalar_t__ uapsd_acvo_en ; 
 scalar_t__ uapsd_enable ; 
 scalar_t__ uapsd_max_sp ; 
 scalar_t__ vcs_type ; 
 scalar_t__ vrtl_carrier_sense ; 
 scalar_t__ wifi_test ; 
 scalar_t__ wireless_mode ; 
 scalar_t__ wmm_enable ; 

__attribute__((used)) static void loadparam(struct _adapter *padapter, struct  net_device *pnetdev)
{
	struct registry_priv  *registry_par = &padapter->registrypriv;

	registry_par->chip_version = (u8)chip_version;
	registry_par->rfintfs = (u8)rfintfs;
	registry_par->lbkmode = (u8)lbkmode;
	registry_par->hci = (u8)hci;
	registry_par->network_mode  = (u8)network_mode;
	memcpy(registry_par->ssid.Ssid, "ANY", 3);
	registry_par->ssid.SsidLength = 3;
	registry_par->channel = (u8)channel;
	registry_par->wireless_mode = (u8)wireless_mode;
	registry_par->vrtl_carrier_sense = (u8)vrtl_carrier_sense;
	registry_par->vcs_type = (u8)vcs_type;
	registry_par->frag_thresh = (u16)frag_thresh;
	registry_par->preamble = (u8)preamble;
	registry_par->scan_mode = (u8)scan_mode;
	registry_par->adhoc_tx_pwr = (u8)adhoc_tx_pwr;
	registry_par->soft_ap = (u8)soft_ap;
	registry_par->smart_ps = (u8)smart_ps;
	registry_par->power_mgnt = (u8)power_mgnt;
	registry_par->radio_enable = (u8)radio_enable;
	registry_par->long_retry_lmt = (u8)long_retry_lmt;
	registry_par->short_retry_lmt = (u8)short_retry_lmt;
	registry_par->busy_thresh = (u16)busy_thresh;
	registry_par->ack_policy = (u8)ack_policy;
	registry_par->mp_mode = (u8)mp_mode;
	registry_par->software_encrypt = (u8)software_encrypt;
	registry_par->software_decrypt = (u8)software_decrypt;
	/*UAPSD*/
	registry_par->wmm_enable = (u8)wmm_enable;
	registry_par->uapsd_enable = (u8)uapsd_enable;
	registry_par->uapsd_max_sp = (u8)uapsd_max_sp;
	registry_par->uapsd_acbk_en = (u8)uapsd_acbk_en;
	registry_par->uapsd_acbe_en = (u8)uapsd_acbe_en;
	registry_par->uapsd_acvi_en = (u8)uapsd_acvi_en;
	registry_par->uapsd_acvo_en = (u8)uapsd_acvo_en;
	registry_par->ht_enable = (u8)ht_enable;
	registry_par->cbw40_enable = (u8)cbw40_enable;
	registry_par->ampdu_enable = (u8)ampdu_enable;
	registry_par->rf_config = (u8)rf_config;
	registry_par->low_power = (u8)low_power;
	registry_par->wifi_test = (u8)wifi_test;
	r8712_initmac = initmac;
}