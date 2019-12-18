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
struct usbnet {int dummy; } ;
struct TYPE_2__ {int legacy; } ;
struct station_info {int /*<<< orphan*/  filled; int /*<<< orphan*/  signal; TYPE_1__ txrate; } ;
typedef  int /*<<< orphan*/  rssi ;
typedef  int /*<<< orphan*/  linkspeed ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int /*<<< orphan*/  RNDIS_OID_802_11_RSSI ; 
 int /*<<< orphan*/  RNDIS_OID_GEN_LINK_SPEED ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  level_to_qual (int) ; 
 int /*<<< orphan*/  memset (struct station_info*,int /*<<< orphan*/ ,int) ; 
 int rndis_query_oid (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void rndis_fill_station_info(struct usbnet *usbdev,
						struct station_info *sinfo)
{
	__le32 linkspeed, rssi;
	int ret, len;

	memset(sinfo, 0, sizeof(*sinfo));

	len = sizeof(linkspeed);
	ret = rndis_query_oid(usbdev, RNDIS_OID_GEN_LINK_SPEED, &linkspeed, &len);
	if (ret == 0) {
		sinfo->txrate.legacy = le32_to_cpu(linkspeed) / 1000;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	}

	len = sizeof(rssi);
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_RSSI,
			      &rssi, &len);
	if (ret == 0) {
		sinfo->signal = level_to_qual(le32_to_cpu(rssi));
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	}
}