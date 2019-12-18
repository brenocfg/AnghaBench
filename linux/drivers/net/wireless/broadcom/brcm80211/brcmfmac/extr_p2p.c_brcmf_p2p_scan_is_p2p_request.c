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
struct cfg80211_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_scan_request {int n_ssids; struct cfg80211_ssid* ssids; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_WILDCARD_SSID ; 
 scalar_t__ BRCMF_P2P_WILDCARD_SSID_LEN ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool brcmf_p2p_scan_is_p2p_request(struct cfg80211_scan_request *request)
{
	struct cfg80211_ssid *ssids = request->ssids;
	int i;

	for (i = 0; i < request->n_ssids; i++) {
		if (ssids[i].ssid_len != BRCMF_P2P_WILDCARD_SSID_LEN)
			continue;

		brcmf_dbg(INFO, "comparing ssid \"%s\"", ssids[i].ssid);
		if (!memcmp(BRCMF_P2P_WILDCARD_SSID, ssids[i].ssid,
			    BRCMF_P2P_WILDCARD_SSID_LEN))
			return true;
	}
	return false;
}