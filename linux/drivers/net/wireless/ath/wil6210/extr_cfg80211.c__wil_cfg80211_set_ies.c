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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wil6210_vif {int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  proberesp_len; int /*<<< orphan*/  proberesp; } ;
struct cfg80211_beacon_data {int /*<<< orphan*/ * tail; int /*<<< orphan*/  tail_len; int /*<<< orphan*/ * assocresp_ies; int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/ * proberesp_ies; int /*<<< orphan*/  probe_resp_len; int /*<<< orphan*/ * probe_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_FRAME_ASSOC_RESP ; 
 int /*<<< orphan*/  WMI_FRAME_BEACON ; 
 int /*<<< orphan*/  WMI_FRAME_PROBE_RESP ; 
 int /*<<< orphan*/ * _wil_cfg80211_get_proberesp_ies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _wil_cfg80211_merge_extra_ies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_memdup_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wmi_set_ie (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _wil_cfg80211_set_ies(struct wil6210_vif *vif,
				 struct cfg80211_beacon_data *bcon)
{
	int rc;
	u16 len = 0, proberesp_len = 0;
	u8 *ies = NULL, *proberesp;

	/* update local storage used for AP recovery */
	wil_memdup_ie(&vif->proberesp, &vif->proberesp_len, bcon->probe_resp,
		      bcon->probe_resp_len);
	wil_memdup_ie(&vif->proberesp_ies, &vif->proberesp_ies_len,
		      bcon->proberesp_ies, bcon->proberesp_ies_len);
	wil_memdup_ie(&vif->assocresp_ies, &vif->assocresp_ies_len,
		      bcon->assocresp_ies, bcon->assocresp_ies_len);

	proberesp = _wil_cfg80211_get_proberesp_ies(bcon->probe_resp,
						    bcon->probe_resp_len,
						    &proberesp_len);
	rc = _wil_cfg80211_merge_extra_ies(proberesp,
					   proberesp_len,
					   bcon->proberesp_ies,
					   bcon->proberesp_ies_len,
					   &ies, &len);

	if (rc)
		goto out;

	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_RESP, len, ies);
	if (rc)
		goto out;

	if (bcon->assocresp_ies)
		rc = wmi_set_ie(vif, WMI_FRAME_ASSOC_RESP,
				bcon->assocresp_ies_len, bcon->assocresp_ies);
	else
		rc = wmi_set_ie(vif, WMI_FRAME_ASSOC_RESP, len, ies);
#if 0 /* to use beacon IE's, remove this #if 0 */
	if (rc)
		goto out;

	rc = wmi_set_ie(vif, WMI_FRAME_BEACON,
			bcon->tail_len, bcon->tail);
#endif
out:
	kfree(ies);
	return rc;
}