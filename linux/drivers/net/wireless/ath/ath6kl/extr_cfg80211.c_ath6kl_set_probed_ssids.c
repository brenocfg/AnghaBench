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
typedef  int u8 ;
struct cfg80211_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_match_set {TYPE_2__ ssid; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct TYPE_6__ {scalar_t__ ssid_len; int /*<<< orphan*/ * ssid; } ;
struct ath6kl_cfg80211_match_probe_ssid {TYPE_3__ ssid; int /*<<< orphan*/  flag; } ;
struct ath6kl {int /*<<< orphan*/  wmi; TYPE_1__* wiphy; } ;
typedef  int /*<<< orphan*/  ssid_list ;
struct TYPE_4__ {scalar_t__ max_match_sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY_SSID_FLAG ; 
 int /*<<< orphan*/  DISABLE_SSID_FLAG ; 
 int EINVAL ; 
 int /*<<< orphan*/  MATCH_SSID_FLAG ; 
 int MAX_PROBED_SSIDS ; 
 int /*<<< orphan*/  SPECIFIC_SSID_FLAG ; 
 int /*<<< orphan*/  ath6kl_wmi_probedssid_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ath6kl_cfg80211_match_probe_ssid*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_set_probed_ssids(struct ath6kl *ar,
				   struct ath6kl_vif *vif,
				   struct cfg80211_ssid *ssids, int n_ssids,
				   struct cfg80211_match_set *match_set,
				   int n_match_ssid)
{
	u8 i, j, index_to_add, ssid_found = false;
	struct ath6kl_cfg80211_match_probe_ssid ssid_list[MAX_PROBED_SSIDS];

	memset(ssid_list, 0, sizeof(ssid_list));

	if (n_ssids > MAX_PROBED_SSIDS ||
	    n_match_ssid > MAX_PROBED_SSIDS)
		return -EINVAL;

	for (i = 0; i < n_ssids; i++) {
		memcpy(ssid_list[i].ssid.ssid,
		       ssids[i].ssid,
		       ssids[i].ssid_len);
		ssid_list[i].ssid.ssid_len = ssids[i].ssid_len;

		if (ssids[i].ssid_len)
			ssid_list[i].flag = SPECIFIC_SSID_FLAG;
		else
			ssid_list[i].flag = ANY_SSID_FLAG;

		if (ar->wiphy->max_match_sets != 0 && n_match_ssid == 0)
			ssid_list[i].flag |= MATCH_SSID_FLAG;
	}

	index_to_add = i;

	for (i = 0; i < n_match_ssid; i++) {
		ssid_found = false;

		for (j = 0; j < n_ssids; j++) {
			if ((match_set[i].ssid.ssid_len ==
			     ssid_list[j].ssid.ssid_len) &&
			    (!memcmp(ssid_list[j].ssid.ssid,
				     match_set[i].ssid.ssid,
				     match_set[i].ssid.ssid_len))) {
				ssid_list[j].flag |= MATCH_SSID_FLAG;
				ssid_found = true;
				break;
			}
		}

		if (ssid_found)
			continue;

		if (index_to_add >= MAX_PROBED_SSIDS)
			continue;

		ssid_list[index_to_add].ssid.ssid_len =
			match_set[i].ssid.ssid_len;
		memcpy(ssid_list[index_to_add].ssid.ssid,
		       match_set[i].ssid.ssid,
		       match_set[i].ssid.ssid_len);
		ssid_list[index_to_add].flag |= MATCH_SSID_FLAG;
		index_to_add++;
	}

	for (i = 0; i < index_to_add; i++) {
		ath6kl_wmi_probedssid_cmd(ar->wmi, vif->fw_vif_idx, i,
					  ssid_list[i].flag,
					  ssid_list[i].ssid.ssid_len,
					  ssid_list[i].ssid.ssid);
	}

	/* Make sure no old entries are left behind */
	for (i = index_to_add; i < MAX_PROBED_SSIDS; i++) {
		ath6kl_wmi_probedssid_cmd(ar->wmi, vif->fw_vif_idx, i,
					  DISABLE_SSID_FLAG, 0, NULL);
	}

	return 0;
}