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
typedef  unsigned char u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct rx_pkt_attrib {int /*<<< orphan*/  src; int /*<<< orphan*/  ra; int /*<<< orphan*/  bssid; } ;
struct recv_frame {TYPE_1__* pkt; struct rx_pkt_attrib attrib; } ;
struct mlme_priv {int dummy; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
struct TYPE_2__ {unsigned char* data; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_88E (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int GetFrameSubType (unsigned char*) ; 
 int RTW_RX_HANDLED ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int WIFI_QOS_DATA_TYPE ; 
 int /*<<< orphan*/  WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_rx_stats (struct adapter*,struct recv_frame*,struct sta_info*) ; 
 unsigned char* get_bssid (struct mlme_priv*) ; 
 int /*<<< orphan*/  issue_deauth (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* myid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_pwrbit_data (struct adapter*,struct recv_frame*) ; 
 int /*<<< orphan*/  process_wmmps_data (struct adapter*,struct recv_frame*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sta2ap_data_frame(struct adapter *adapter,
			     struct recv_frame *precv_frame,
			     struct sta_info **psta)
{
	struct rx_pkt_attrib *pattrib = &precv_frame->attrib;
	struct	sta_priv *pstapriv = &adapter->stapriv;
	struct	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *ptr = precv_frame->pkt->data;
	unsigned char *mybssid  = get_bssid(pmlmepriv);
	int ret = _SUCCESS;

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		/* For AP mode, RA = BSSID, TX = STA(SRC_ADDR), A3 = DST_ADDR */
		if (memcmp(pattrib->bssid, mybssid, ETH_ALEN)) {
			ret = _FAIL;
			goto exit;
		}

		*psta = rtw_get_stainfo(pstapriv, pattrib->src);
		if (!*psta) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("can't get psta under AP_MODE; drop pkt\n"));
			DBG_88E("issue_deauth to sta=%pM for the reason(7)\n", (pattrib->src));

			issue_deauth(adapter, pattrib->src, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);

			ret = RTW_RX_HANDLED;
			goto exit;
		}

		process_pwrbit_data(adapter, precv_frame);

		if ((GetFrameSubType(ptr) & WIFI_QOS_DATA_TYPE) == WIFI_QOS_DATA_TYPE)
			process_wmmps_data(adapter, precv_frame);

		if (GetFrameSubType(ptr) & BIT(6)) {
			/* No data, will not indicate to upper layer, temporily count it here */
			count_rx_stats(adapter, precv_frame, *psta);
			ret = RTW_RX_HANDLED;
			goto exit;
		}
	} else {
		u8 *myhwaddr = myid(&adapter->eeprompriv);

		if (memcmp(pattrib->ra, myhwaddr, ETH_ALEN)) {
			ret = RTW_RX_HANDLED;
			goto exit;
		}
		DBG_88E("issue_deauth to sta=%pM for the reason(7)\n", (pattrib->src));
		issue_deauth(adapter, pattrib->src, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
		ret = RTW_RX_HANDLED;
		goto exit;
	}

exit:

	return ret;
}