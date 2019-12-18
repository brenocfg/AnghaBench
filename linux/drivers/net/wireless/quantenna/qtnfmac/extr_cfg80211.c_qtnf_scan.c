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
struct wiphy {int dummy; } ;
struct qtnf_wmac {int /*<<< orphan*/  scan_timeout; TYPE_1__* bus; int /*<<< orphan*/  macid; struct cfg80211_scan_request* scan_req; } ;
struct cfg80211_scan_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int HZ ; 
 int QTNF_SCAN_TIMEOUT_SEC ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send_scan (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int
qtnf_scan(struct wiphy *wiphy, struct cfg80211_scan_request *request)
{
	struct qtnf_wmac *mac = wiphy_priv(wiphy);
	int ret;

	cancel_delayed_work_sync(&mac->scan_timeout);

	mac->scan_req = request;

	ret = qtnf_cmd_send_scan(mac);
	if (ret) {
		pr_err("MAC%u: failed to start scan\n", mac->macid);
		mac->scan_req = NULL;
		goto out;
	}

	pr_debug("MAC%u: scan started\n", mac->macid);
	queue_delayed_work(mac->bus->workqueue, &mac->scan_timeout,
			   QTNF_SCAN_TIMEOUT_SEC * HZ);

out:
	return ret;
}