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
typedef  unsigned int uint ;
typedef  int u8 ;
struct ndis_802_11_var_ie {int ElementID; scalar_t__ Length; int /*<<< orphan*/  data; } ;
struct ndis_802_11_fixed_ie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRGOCAP_OUI ; 
 int /*<<< orphan*/  ARTHEROS_OUI1 ; 
 int /*<<< orphan*/  ARTHEROS_OUI2 ; 
 int /*<<< orphan*/  BROADCOM_OUI1 ; 
 int /*<<< orphan*/  BROADCOM_OUI2 ; 
 int /*<<< orphan*/  CISCO_OUI ; 
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  EPIGRAM_OUI ; 
 unsigned char HT_IOT_PEER_AIRGO ; 
 unsigned char HT_IOT_PEER_ATHEROS ; 
 unsigned char HT_IOT_PEER_BROADCOM ; 
 unsigned char HT_IOT_PEER_CISCO ; 
 unsigned char HT_IOT_PEER_MARVELL ; 
 unsigned char HT_IOT_PEER_RALINK ; 
 unsigned char HT_IOT_PEER_REALTEK ; 
 unsigned char HT_IOT_PEER_TENDA ; 
 unsigned char HT_IOT_PEER_UNKNOWN ; 
 int /*<<< orphan*/  MARVELL_OUI ; 
 int /*<<< orphan*/  RALINK_OUI ; 
 int /*<<< orphan*/  REALTEK_OUI ; 
#define  _VENDOR_SPECIFIC_IE_ 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

unsigned char check_assoc_AP(u8 *pframe, uint len)
{
	unsigned int i;
	struct ndis_802_11_var_ie *pIE;
	u8 epigram_vendor_flag;
	u8 ralink_vendor_flag;

	epigram_vendor_flag = 0;
	ralink_vendor_flag = 0;

	for (i = sizeof(struct ndis_802_11_fixed_ie); i < len;) {
		pIE = (struct ndis_802_11_var_ie *)(pframe + i);

		switch (pIE->ElementID) {
		case _VENDOR_SPECIFIC_IE_:
			if ((!memcmp(pIE->data, ARTHEROS_OUI1, 3)) ||
			    (!memcmp(pIE->data, ARTHEROS_OUI2, 3))) {
				DBG_88E("link to Artheros AP\n");
				return HT_IOT_PEER_ATHEROS;
			} else if ((!memcmp(pIE->data, BROADCOM_OUI1, 3)) ||
				   (!memcmp(pIE->data, BROADCOM_OUI2, 3))) {
				DBG_88E("link to Broadcom AP\n");
				return HT_IOT_PEER_BROADCOM;
			} else if (!memcmp(pIE->data, MARVELL_OUI, 3)) {
				DBG_88E("link to Marvell AP\n");
				return HT_IOT_PEER_MARVELL;
			} else if (!memcmp(pIE->data, RALINK_OUI, 3)) {
				if (!ralink_vendor_flag) {
					ralink_vendor_flag = 1;
				} else {
					DBG_88E("link to Ralink AP\n");
					return HT_IOT_PEER_RALINK;
				}
			} else if (!memcmp(pIE->data, CISCO_OUI, 3)) {
				DBG_88E("link to Cisco AP\n");
				return HT_IOT_PEER_CISCO;
			} else if (!memcmp(pIE->data, REALTEK_OUI, 3)) {
				DBG_88E("link to Realtek 96B\n");
				return HT_IOT_PEER_REALTEK;
			} else if (!memcmp(pIE->data, AIRGOCAP_OUI, 3)) {
				DBG_88E("link to Airgo Cap\n");
				return HT_IOT_PEER_AIRGO;
			} else if (!memcmp(pIE->data, EPIGRAM_OUI, 3)) {
				epigram_vendor_flag = 1;
				if (ralink_vendor_flag) {
					DBG_88E("link to Tenda W311R AP\n");
					return HT_IOT_PEER_TENDA;
				} else {
					DBG_88E("Capture EPIGRAM_OUI\n");
				}
			} else {
				break;
			}

		default:
			break;
		}
		i += (pIE->Length + 2);
	}

	if (ralink_vendor_flag && !epigram_vendor_flag) {
		DBG_88E("link to Ralink AP\n");
		return HT_IOT_PEER_RALINK;
	} else if (ralink_vendor_flag && epigram_vendor_flag) {
		DBG_88E("link to Tenda W311R AP\n");
		return HT_IOT_PEER_TENDA;
	} else {
		DBG_88E("link to new AP\n");
		return HT_IOT_PEER_UNKNOWN;
	}
}