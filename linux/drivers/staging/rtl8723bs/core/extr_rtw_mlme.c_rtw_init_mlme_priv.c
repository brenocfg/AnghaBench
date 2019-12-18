#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlan_network {int /*<<< orphan*/  list; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  InfrastructureMode; } ;
struct TYPE_5__ {TYPE_1__ network; } ;
struct mlme_priv {int roam_flags; int /*<<< orphan*/  roam_scan_int_ms; int /*<<< orphan*/  roam_rssi_diff_th; int /*<<< orphan*/  roam_scanr_exp_ms; TYPE_3__ free_bss_pool; int /*<<< orphan*/ * free_bss_buf; int /*<<< orphan*/  assoc_ssid; TYPE_3__ scanned_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  scan_mode; TYPE_2__ cur_network; int /*<<< orphan*/  fw_state; int /*<<< orphan*/ * pscanned; int /*<<< orphan*/ * nic_hdl; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_BSS_CNT ; 
 int /*<<< orphan*/  Ndis802_11AutoUnknown ; 
 int RTW_ROAM_ACTIVE ; 
 int RTW_ROAM_ON_EXPIRED ; 
 int RTW_ROAM_ON_RESUME ; 
 int /*<<< orphan*/  RTW_ROAM_RSSI_DIFF_TH ; 
 int /*<<< orphan*/  RTW_ROAM_SCAN_INTERVAL_MS ; 
 int /*<<< orphan*/  RTW_ROAM_SCAN_RESULT_EXP_MS ; 
 int /*<<< orphan*/  SCAN_ACTIVE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_clear_scan_deny (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_mlme_timer (struct adapter*) ; 
 int /*<<< orphan*/  set_scanned_network_val (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int /*<<< orphan*/ ) ; 

int	rtw_init_mlme_priv(struct adapter *padapter)
{
	int	i;
	u8 *pbuf;
	struct wlan_network	*pnetwork;
	struct mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	int	res = _SUCCESS;

	pmlmepriv->nic_hdl = (u8 *)padapter;

	pmlmepriv->pscanned = NULL;
	pmlmepriv->fw_state = WIFI_STATION_STATE; /*  Must sync with rtw_wdev_alloc() */
	/*  wdev->iftype = NL80211_IFTYPE_STATION */
	pmlmepriv->cur_network.network.InfrastructureMode = Ndis802_11AutoUnknown;
	pmlmepriv->scan_mode = SCAN_ACTIVE;/*  1: active, 0: pasive. Maybe someday we should rename this varable to "active_mode" (Jeff) */

	spin_lock_init(&pmlmepriv->lock);
	_rtw_init_queue(&pmlmepriv->free_bss_pool);
	_rtw_init_queue(&pmlmepriv->scanned_queue);

	set_scanned_network_val(pmlmepriv, 0);

	memset(&pmlmepriv->assoc_ssid, 0, sizeof(struct ndis_802_11_ssid));

	pbuf = vzalloc(array_size(MAX_BSS_CNT, sizeof(struct wlan_network)));

	if (pbuf == NULL) {
		res = _FAIL;
		goto exit;
	}
	pmlmepriv->free_bss_buf = pbuf;

	pnetwork = (struct wlan_network *)pbuf;

	for (i = 0; i < MAX_BSS_CNT; i++) {
		INIT_LIST_HEAD(&pnetwork->list);

		list_add_tail(&pnetwork->list, &pmlmepriv->free_bss_pool.queue);

		pnetwork++;
	}

	/* allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf */

	rtw_clear_scan_deny(padapter);

	#define RTW_ROAM_SCAN_RESULT_EXP_MS 5000
	#define RTW_ROAM_RSSI_DIFF_TH 10
	#define RTW_ROAM_SCAN_INTERVAL_MS 10000

	pmlmepriv->roam_flags = 0
		| RTW_ROAM_ON_EXPIRED
		| RTW_ROAM_ON_RESUME
		#ifdef CONFIG_LAYER2_ROAMING_ACTIVE /* FIXME */
		| RTW_ROAM_ACTIVE
		#endif
		;

	pmlmepriv->roam_scanr_exp_ms = RTW_ROAM_SCAN_RESULT_EXP_MS;
	pmlmepriv->roam_rssi_diff_th = RTW_ROAM_RSSI_DIFF_TH;
	pmlmepriv->roam_scan_int_ms = RTW_ROAM_SCAN_INTERVAL_MS;

	rtw_init_mlme_timer(padapter);

exit:

	return res;
}