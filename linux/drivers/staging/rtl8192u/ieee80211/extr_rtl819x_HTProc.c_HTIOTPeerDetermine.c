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
struct TYPE_3__ {scalar_t__ bdRT2RTAggregation; } ;
struct ieee80211_network {int /*<<< orphan*/  bssid; scalar_t__ atheros_cap_exist; scalar_t__ ralink_cap_exist; scalar_t__ broadcom_cap_exist; TYPE_1__ bssht; } ;
struct ieee80211_device {struct ieee80211_network current_network; TYPE_2__* pHTInfo; } ;
struct TYPE_4__ {void* IOTPeer; } ;
typedef  TYPE_2__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  AIRLINK_RALINK ; 
 int /*<<< orphan*/  BELKINF5D82334V3_RALINK ; 
 int /*<<< orphan*/  BELKINF5D8233V1_RALINK ; 
 int /*<<< orphan*/  CISCO_BROADCOM ; 
 int /*<<< orphan*/  EDIMAX_RALINK ; 
 void* HT_IOT_PEER_ATHEROS ; 
 void* HT_IOT_PEER_BROADCOM ; 
 void* HT_IOT_PEER_CISCO ; 
 void* HT_IOT_PEER_RALINK ; 
 void* HT_IOT_PEER_REALTEK ; 
 void* HT_IOT_PEER_UNKNOWN ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  IEEE80211_DL_IOT ; 
 int /*<<< orphan*/  LINKSYSWRT330_LINKSYSWRT300_BROADCOM ; 
 int /*<<< orphan*/  LINKSYSWRT350_LINKSYSWRT150_BROADCOM ; 
 int /*<<< orphan*/  NETGEAR834Bv2_BROADCOM ; 
 int /*<<< orphan*/  PCI_RALINK ; 
 int /*<<< orphan*/  UNKNOWN_BORADCOM ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void HTIOTPeerDetermine(struct ieee80211_device *ieee)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	struct ieee80211_network *net = &ieee->current_network;

	if (net->bssht.bdRT2RTAggregation)
		pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK;
	else if (net->broadcom_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	else if ((memcmp(net->bssid, UNKNOWN_BORADCOM, 3) == 0) ||
		 (memcmp(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) == 0) ||
		 (memcmp(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) == 0) ||
		 (memcmp(net->bssid, NETGEAR834Bv2_BROADCOM, 3) == 0))
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	else if ((memcmp(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, PCI_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, EDIMAX_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, AIRLINK_RALINK, 3) == 0) ||
		 net->ralink_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_RALINK;
	else if (net->atheros_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_ATHEROS;
	else if (memcmp(net->bssid, CISCO_BROADCOM, 3) == 0)
		pHTInfo->IOTPeer = HT_IOT_PEER_CISCO;
	else
		pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;

	IEEE80211_DEBUG(IEEE80211_DL_IOT, "Joseph debug!! IOTPEER: %x\n", pHTInfo->IOTPeer);
}