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
struct cfg80211_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_sched_scan_request {int n_ssids; TYPE_1__* ssids; } ;
struct TYPE_2__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool brcmf_is_ssid_active(struct cfg80211_ssid *ssid,
				 struct cfg80211_sched_scan_request *req)
{
	int i;

	if (!ssid || !req->ssids || !req->n_ssids)
		return false;

	for (i = 0; i < req->n_ssids; i++) {
		if (ssid->ssid_len == req->ssids[i].ssid_len) {
			if (!strncmp(ssid->ssid, req->ssids[i].ssid,
				     ssid->ssid_len))
				return true;
		}
	}
	return false;
}