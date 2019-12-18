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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_BE ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_BK ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_VI ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_VO ; 
 int /*<<< orphan*/  SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_TLV_TDLS_PEER_QOS_AC_BE ; 
 int /*<<< orphan*/  WMI_TLV_TDLS_PEER_QOS_AC_BK ; 
 int /*<<< orphan*/  WMI_TLV_TDLS_PEER_QOS_AC_VI ; 
 int /*<<< orphan*/  WMI_TLV_TDLS_PEER_QOS_AC_VO ; 
 int /*<<< orphan*/  WMI_TLV_TDLS_PEER_SP ; 

__attribute__((used)) static u32 ath10k_wmi_tlv_prepare_peer_qos(u8 uapsd_queues, u8 sp)
{
	u32 peer_qos = 0;

	if (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_VO;
	if (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_VI;
	if (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_BK;
	if (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_BE;

	peer_qos |= SM(sp, WMI_TLV_TDLS_PEER_SP);

	return peer_qos;
}