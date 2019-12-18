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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_cmd_sched_scan_ssid_list {size_t n_ssids; TYPE_2__* ssids; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct cfg80211_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_sched_scan_request {int n_match_sets; int n_ssids; struct cfg80211_ssid* ssids; struct cfg80211_match_set* match_sets; } ;
struct TYPE_3__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_match_set {TYPE_1__ ssid; } ;
struct TYPE_4__ {scalar_t__ len; void* type; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONNECTION_SCAN_SSID_CFG ; 
 int DEBUG_CMD ; 
 int DEBUG_SCAN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCAN_SSID_FILTER_ANY ; 
 int SCAN_SSID_FILTER_DISABLED ; 
 int SCAN_SSID_FILTER_LIST ; 
 void* SCAN_SSID_TYPE_HIDDEN ; 
 void* SCAN_SSID_TYPE_PUBLIC ; 
 int /*<<< orphan*/  kfree (struct wl1271_cmd_sched_scan_ssid_list*) ; 
 struct wl1271_cmd_sched_scan_ssid_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_sched_scan_ssid_list*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int
wlcore_scan_sched_scan_ssid_list(struct wl1271 *wl,
				 struct wl12xx_vif *wlvif,
				 struct cfg80211_sched_scan_request *req)
{
	struct wl1271_cmd_sched_scan_ssid_list *cmd = NULL;
	struct cfg80211_match_set *sets = req->match_sets;
	struct cfg80211_ssid *ssids = req->ssids;
	int ret = 0, type, i, j, n_match_ssids = 0;

	wl1271_debug((DEBUG_CMD | DEBUG_SCAN), "cmd sched scan ssid list");

	/* count the match sets that contain SSIDs */
	for (i = 0; i < req->n_match_sets; i++)
		if (sets[i].ssid.ssid_len > 0)
			n_match_ssids++;

	/* No filter, no ssids or only bcast ssid */
	if (!n_match_ssids &&
	    (!req->n_ssids ||
	     (req->n_ssids == 1 && req->ssids[0].ssid_len == 0))) {
		type = SCAN_SSID_FILTER_ANY;
		goto out;
	}

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->role_id = wlvif->role_id;
	if (!n_match_ssids) {
		/* No filter, with ssids */
		type = SCAN_SSID_FILTER_DISABLED;

		for (i = 0; i < req->n_ssids; i++) {
			cmd->ssids[cmd->n_ssids].type = (ssids[i].ssid_len) ?
				SCAN_SSID_TYPE_HIDDEN : SCAN_SSID_TYPE_PUBLIC;
			cmd->ssids[cmd->n_ssids].len = ssids[i].ssid_len;
			memcpy(cmd->ssids[cmd->n_ssids].ssid, ssids[i].ssid,
			       ssids[i].ssid_len);
			cmd->n_ssids++;
		}
	} else {
		type = SCAN_SSID_FILTER_LIST;

		/* Add all SSIDs from the filters */
		for (i = 0; i < req->n_match_sets; i++) {
			/* ignore sets without SSIDs */
			if (!sets[i].ssid.ssid_len)
				continue;

			cmd->ssids[cmd->n_ssids].type = SCAN_SSID_TYPE_PUBLIC;
			cmd->ssids[cmd->n_ssids].len = sets[i].ssid.ssid_len;
			memcpy(cmd->ssids[cmd->n_ssids].ssid,
			       sets[i].ssid.ssid, sets[i].ssid.ssid_len);
			cmd->n_ssids++;
		}
		if ((req->n_ssids > 1) ||
		    (req->n_ssids == 1 && req->ssids[0].ssid_len > 0)) {
			/*
			 * Mark all the SSIDs passed in the SSID list as HIDDEN,
			 * so they're used in probe requests.
			 */
			for (i = 0; i < req->n_ssids; i++) {
				if (!req->ssids[i].ssid_len)
					continue;

				for (j = 0; j < cmd->n_ssids; j++)
					if ((req->ssids[i].ssid_len ==
					     cmd->ssids[j].len) &&
					    !memcmp(req->ssids[i].ssid,
						   cmd->ssids[j].ssid,
						   req->ssids[i].ssid_len)) {
						cmd->ssids[j].type =
							SCAN_SSID_TYPE_HIDDEN;
						break;
					}
				/* Fail if SSID isn't present in the filters */
				if (j == cmd->n_ssids) {
					ret = -EINVAL;
					goto out_free;
				}
			}
		}
	}

	ret = wl1271_cmd_send(wl, CMD_CONNECTION_SCAN_SSID_CFG, cmd,
			      sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("cmd sched scan ssid list failed");
		goto out_free;
	}

out_free:
	kfree(cmd);
out:
	if (ret < 0)
		return ret;
	return type;
}