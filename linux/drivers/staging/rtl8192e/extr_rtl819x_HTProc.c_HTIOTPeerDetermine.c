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
struct TYPE_2__ {int RT2RT_HT_Mode; scalar_t__ bdRT2RTAggregation; } ;
struct rtllib_network {scalar_t__ airgo_cap_exist; scalar_t__ marvell_cap_exist; int /*<<< orphan*/  bssid; scalar_t__ cisco_cap_exist; scalar_t__ atheros_cap_exist; scalar_t__ ralink_cap_exist; scalar_t__ broadcom_cap_exist; TYPE_1__ bssht; } ;
struct rtllib_device {int /*<<< orphan*/  dev; struct rtllib_network current_network; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {void* IOTPeer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRLINK_RALINK ; 
 int /*<<< orphan*/  BELKINF5D82334V3_RALINK ; 
 int /*<<< orphan*/  BELKINF5D8233V1_RALINK ; 
 int /*<<< orphan*/  CISCO_BROADCOM ; 
 int /*<<< orphan*/  DLINK_ATHEROS_1 ; 
 int /*<<< orphan*/  DLINK_ATHEROS_2 ; 
 int /*<<< orphan*/  EDIMAX_RALINK ; 
 void* HT_IOT_PEER_92U_SOFTAP ; 
 void* HT_IOT_PEER_AIRGO ; 
 void* HT_IOT_PEER_ATHEROS ; 
 void* HT_IOT_PEER_BROADCOM ; 
 void* HT_IOT_PEER_CISCO ; 
 void* HT_IOT_PEER_MARVELL ; 
 void* HT_IOT_PEER_RALINK ; 
 void* HT_IOT_PEER_REALTEK ; 
 void* HT_IOT_PEER_REALTEK_92SE ; 
 void* HT_IOT_PEER_UNKNOWN ; 
 int /*<<< orphan*/  LINKSYSWRT330_LINKSYSWRT300_BROADCOM ; 
 int /*<<< orphan*/  LINKSYSWRT350_LINKSYSWRT150_BROADCOM ; 
 int /*<<< orphan*/  LINKSYS_MARVELL_4400N ; 
 int /*<<< orphan*/  PCI_RALINK ; 
 int RT_HT_CAP_USE_92SE ; 
 int RT_HT_CAP_USE_SOFTAP ; 
 int /*<<< orphan*/  UNKNOWN_BORADCOM ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static void HTIOTPeerDetermine(struct rtllib_device *ieee)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	struct rtllib_network *net = &ieee->current_network;

	if (net->bssht.bdRT2RTAggregation) {
		pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK;
		if (net->bssht.RT2RT_HT_Mode & RT_HT_CAP_USE_92SE)
			pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK_92SE;
		if (net->bssht.RT2RT_HT_Mode & RT_HT_CAP_USE_SOFTAP)
			pHTInfo->IOTPeer = HT_IOT_PEER_92U_SOFTAP;
	} else if (net->broadcom_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	else if (!memcmp(net->bssid, UNKNOWN_BORADCOM, 3) ||
		 !memcmp(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) ||
		 !memcmp(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3))
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	else if ((memcmp(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, PCI_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, EDIMAX_RALINK, 3) == 0) ||
		 (memcmp(net->bssid, AIRLINK_RALINK, 3) == 0) ||
		  net->ralink_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_RALINK;
	else if ((net->atheros_cap_exist) ||
		(memcmp(net->bssid, DLINK_ATHEROS_1, 3) == 0) ||
		(memcmp(net->bssid, DLINK_ATHEROS_2, 3) == 0))
		pHTInfo->IOTPeer = HT_IOT_PEER_ATHEROS;
	else if ((memcmp(net->bssid, CISCO_BROADCOM, 3) == 0) ||
		  net->cisco_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_CISCO;
	else if ((memcmp(net->bssid, LINKSYS_MARVELL_4400N, 3) == 0) ||
		  net->marvell_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_MARVELL;
	else if (net->airgo_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_AIRGO;
	else
		pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;

	netdev_dbg(ieee->dev, "IOTPEER: %x\n", pHTInfo->IOTPeer);
}