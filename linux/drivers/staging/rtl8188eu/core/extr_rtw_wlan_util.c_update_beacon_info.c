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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
struct ndis_802_11_var_ie {int ElementID; scalar_t__ Length; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERP_IE_handler (struct adapter*,struct ndis_802_11_var_ie*) ; 
 int /*<<< orphan*/  VCS_update (struct adapter*,struct sta_info*) ; 
 int WLAN_HDR_A3_LEN ; 
 int _BEACON_IE_OFFSET_ ; 
#define  _ERPINFO_IE_ 129 
#define  _HT_EXTRA_INFO_IE_ 128 
 int /*<<< orphan*/  bwmode_update_check (struct adapter*,struct ndis_802_11_var_ie*) ; 

void update_beacon_info(struct adapter *padapter, u8 *pframe, uint pkt_len, struct sta_info *psta)
{
	unsigned int i;
	unsigned int len;
	struct ndis_802_11_var_ie *pIE;

	len = pkt_len - (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN);

	for (i = 0; i < len;) {
		pIE = (struct ndis_802_11_var_ie *)(pframe + (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN) + i);

		switch (pIE->ElementID) {
		case _HT_EXTRA_INFO_IE_:	/* HT info */
			bwmode_update_check(padapter, pIE);
			break;
		case _ERPINFO_IE_:
			ERP_IE_handler(padapter, pIE);
			VCS_update(padapter, psta);
			break;
		default:
			break;
		}

		i += (pIE->Length + 2);
	}
}