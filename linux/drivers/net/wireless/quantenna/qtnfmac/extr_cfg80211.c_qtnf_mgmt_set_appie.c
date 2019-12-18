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
struct qtnf_vif {int dummy; } ;
struct cfg80211_beacon_data {int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/ * assocresp_ies; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/ * proberesp_ies; int /*<<< orphan*/  beacon_ies_len; int /*<<< orphan*/ * beacon_ies; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLINK_IE_SET_ASSOC_RESP ; 
 int /*<<< orphan*/  QLINK_IE_SET_BEACON_IES ; 
 int /*<<< orphan*/  QLINK_IE_SET_PROBE_RESP_IES ; 
 int qtnf_cmd_send_mgmt_set_appie (struct qtnf_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtnf_mgmt_set_appie(struct qtnf_vif *vif,
			       const struct cfg80211_beacon_data *info)
{
	int ret = 0;

	if (!info->beacon_ies || !info->beacon_ies_len) {
		ret = qtnf_cmd_send_mgmt_set_appie(vif, QLINK_IE_SET_BEACON_IES,
						   NULL, 0);
	} else {
		ret = qtnf_cmd_send_mgmt_set_appie(vif, QLINK_IE_SET_BEACON_IES,
						   info->beacon_ies,
						   info->beacon_ies_len);
	}

	if (ret)
		goto out;

	if (!info->proberesp_ies || !info->proberesp_ies_len) {
		ret = qtnf_cmd_send_mgmt_set_appie(vif,
						   QLINK_IE_SET_PROBE_RESP_IES,
						   NULL, 0);
	} else {
		ret = qtnf_cmd_send_mgmt_set_appie(vif,
						   QLINK_IE_SET_PROBE_RESP_IES,
						   info->proberesp_ies,
						   info->proberesp_ies_len);
	}

	if (ret)
		goto out;

	if (!info->assocresp_ies || !info->assocresp_ies_len) {
		ret = qtnf_cmd_send_mgmt_set_appie(vif,
						   QLINK_IE_SET_ASSOC_RESP,
						   NULL, 0);
	} else {
		ret = qtnf_cmd_send_mgmt_set_appie(vif,
						   QLINK_IE_SET_ASSOC_RESP,
						   info->assocresp_ies,
						   info->assocresp_ies_len);
	}

out:
	return ret;
}