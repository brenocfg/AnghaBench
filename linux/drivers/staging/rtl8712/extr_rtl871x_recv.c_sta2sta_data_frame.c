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
struct rx_pkt_attrib {int /*<<< orphan*/ * src; int /*<<< orphan*/ * ta; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * ra; int /*<<< orphan*/ * bssid; } ;
struct TYPE_4__ {struct rx_pkt_attrib attrib; int /*<<< orphan*/ * rx_data; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_pktloss; } ;
struct _adapter {TYPE_3__ mppriv; int /*<<< orphan*/  eeprompriv; struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/ * GetAddr1Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetAddr2Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetAddr3Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_bssid (struct mlme_priv*) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * myid (int /*<<< orphan*/ *) ; 
 struct sta_info* r8712_get_bcmc_stainfo (struct _adapter*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sint sta2sta_data_frame(struct _adapter *adapter,
			       union recv_frame *precv_frame,
			       struct sta_info **psta)
{
	u8 *ptr = precv_frame->u.hdr.rx_data;
	sint ret = _SUCCESS;
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	struct	sta_priv *pstapriv = &adapter->stapriv;
	struct	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	u8 *sta_addr = NULL;
	bool bmcast = is_multicast_ether_addr(pattrib->dst);

	if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) {
		/* filter packets that SA is myself or multicast or broadcast */
		if (!memcmp(myhwaddr, pattrib->src, ETH_ALEN))
			return _FAIL;
		if ((memcmp(myhwaddr, pattrib->dst, ETH_ALEN)) && (!bmcast))
			return _FAIL;
		if (is_zero_ether_addr(pattrib->bssid) ||
		    is_zero_ether_addr(mybssid) ||
		    (memcmp(pattrib->bssid, mybssid, ETH_ALEN)))
			return _FAIL;
		sta_addr = pattrib->src;
	} else if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
		/* For Station mode, sa and bssid should always be BSSID,
		 * and DA is my mac-address
		 */
		if (memcmp(pattrib->bssid, pattrib->src, ETH_ALEN))
			return _FAIL;
		sta_addr = pattrib->bssid;
	} else if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		if (bmcast) {
			/* For AP mode, if DA == MCAST, then BSSID should
			 * be also MCAST
			 */
			if (!is_multicast_ether_addr(pattrib->bssid))
				return _FAIL;
		} else { /* not mc-frame */
			/* For AP mode, if DA is non-MCAST, then it must be
			 * BSSID, and bssid == BSSID
			 */
			if (memcmp(pattrib->bssid, pattrib->dst, ETH_ALEN))
				return _FAIL;
			sta_addr = pattrib->src;
		}
	} else if (check_fwstate(pmlmepriv, WIFI_MP_STATE)) {
		memcpy(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		memcpy(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		memcpy(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
		memcpy(pattrib->ta, pattrib->src, ETH_ALEN);
		sta_addr = mybssid;
	} else {
		ret  = _FAIL;
	}
	if (bmcast)
		*psta = r8712_get_bcmc_stainfo(adapter);
	else
		*psta = r8712_get_stainfo(pstapriv, sta_addr); /* get ap_info */
	if (*psta == NULL) {
		if (check_fwstate(pmlmepriv, WIFI_MP_STATE))
			adapter->mppriv.rx_pktloss++;
		return _FAIL;
	}
	return ret;
}