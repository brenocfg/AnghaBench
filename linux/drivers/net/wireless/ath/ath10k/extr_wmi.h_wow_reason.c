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
typedef  enum wmi_wow_wake_reason { ____Placeholder_wmi_wow_wake_reason } wmi_wow_wake_reason ;

/* Variables and functions */
 int /*<<< orphan*/  C2S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WOW_REASON_AP_ASSOC_LOST ; 
 int /*<<< orphan*/  WOW_REASON_ASSOC_REQ_RECV ; 
 int /*<<< orphan*/  WOW_REASON_AUTH_REQ_RECV ; 
 int /*<<< orphan*/  WOW_REASON_BEACON_RECV ; 
 int /*<<< orphan*/  WOW_REASON_CLIENT_KICKOUT_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_CSA_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_DEAUTH_RECVD ; 
 int /*<<< orphan*/  WOW_REASON_DEBUG_TEST ; 
 int /*<<< orphan*/  WOW_REASON_DFS_PHYERR_RADADR_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_DISASSOC_RECVD ; 
 int /*<<< orphan*/  WOW_REASON_EAP_REQ ; 
 int /*<<< orphan*/  WOW_REASON_FOURWAY_HS_RECV ; 
 int /*<<< orphan*/  WOW_REASON_GTK_HS_ERR ; 
 int /*<<< orphan*/  WOW_REASON_HOST_AUTO_SHUTDOWN ; 
 int /*<<< orphan*/  WOW_REASON_HTT_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_IOAC_EXTEND_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_IOAC_MAGIC_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_IOAC_SHORT_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_IOAC_TIMER_EVENT ; 
 int /*<<< orphan*/  WOW_REASON_LOW_RSSI ; 
 int /*<<< orphan*/  WOW_REASON_NLOD ; 
 int /*<<< orphan*/  WOW_REASON_P2P_DISC ; 
 int /*<<< orphan*/  WOW_REASON_PATTERN_MATCH_FOUND ; 
 int /*<<< orphan*/  WOW_REASON_PROBE_REQ_WPS_IE_RECV ; 
 int /*<<< orphan*/  WOW_REASON_RA_MATCH ; 
 int /*<<< orphan*/  WOW_REASON_RECV_MAGIC_PATTERN ; 
 int /*<<< orphan*/  WOW_REASON_ROAM_HO ; 
 int /*<<< orphan*/  WOW_REASON_TIMER_INTR_RECV ; 
 int /*<<< orphan*/  WOW_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  WOW_REASON_WLAN_HB ; 

__attribute__((used)) static inline const char *wow_reason(enum wmi_wow_wake_reason reason)
{
	switch (reason) {
	C2S(WOW_REASON_UNSPECIFIED);
	C2S(WOW_REASON_NLOD);
	C2S(WOW_REASON_AP_ASSOC_LOST);
	C2S(WOW_REASON_LOW_RSSI);
	C2S(WOW_REASON_DEAUTH_RECVD);
	C2S(WOW_REASON_DISASSOC_RECVD);
	C2S(WOW_REASON_GTK_HS_ERR);
	C2S(WOW_REASON_EAP_REQ);
	C2S(WOW_REASON_FOURWAY_HS_RECV);
	C2S(WOW_REASON_TIMER_INTR_RECV);
	C2S(WOW_REASON_PATTERN_MATCH_FOUND);
	C2S(WOW_REASON_RECV_MAGIC_PATTERN);
	C2S(WOW_REASON_P2P_DISC);
	C2S(WOW_REASON_WLAN_HB);
	C2S(WOW_REASON_CSA_EVENT);
	C2S(WOW_REASON_PROBE_REQ_WPS_IE_RECV);
	C2S(WOW_REASON_AUTH_REQ_RECV);
	C2S(WOW_REASON_ASSOC_REQ_RECV);
	C2S(WOW_REASON_HTT_EVENT);
	C2S(WOW_REASON_RA_MATCH);
	C2S(WOW_REASON_HOST_AUTO_SHUTDOWN);
	C2S(WOW_REASON_IOAC_MAGIC_EVENT);
	C2S(WOW_REASON_IOAC_SHORT_EVENT);
	C2S(WOW_REASON_IOAC_EXTEND_EVENT);
	C2S(WOW_REASON_IOAC_TIMER_EVENT);
	C2S(WOW_REASON_ROAM_HO);
	C2S(WOW_REASON_DFS_PHYERR_RADADR_EVENT);
	C2S(WOW_REASON_BEACON_RECV);
	C2S(WOW_REASON_CLIENT_KICKOUT_EVENT);
	C2S(WOW_REASON_DEBUG_TEST);
	default:
		return NULL;
	}
}