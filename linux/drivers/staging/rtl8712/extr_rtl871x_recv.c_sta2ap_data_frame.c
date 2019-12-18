#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int /*<<< orphan*/  src; int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 unsigned char* get_bssid (struct mlme_priv*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sint sta2ap_data_frame(struct _adapter *adapter,
			      union recv_frame *precv_frame,
			      struct sta_info **psta)
{
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	struct	sta_priv *pstapriv = &adapter->stapriv;
	struct	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	unsigned char *mybssid  = get_bssid(pmlmepriv);

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		/* For AP mode, if DA is non-MCAST, then it must be BSSID,
		 * and bssid == BSSID
		 * For AP mode, RA=BSSID, TX=STA(SRC_ADDR), A3=DST_ADDR
		 */
		if (memcmp(pattrib->bssid, mybssid, ETH_ALEN))
			return _FAIL;
		*psta = r8712_get_stainfo(pstapriv, pattrib->src);
		if (*psta == NULL)
			return _FAIL;
	}
	return _SUCCESS;
}