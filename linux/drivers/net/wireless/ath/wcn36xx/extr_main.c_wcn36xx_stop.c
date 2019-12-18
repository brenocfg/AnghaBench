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
struct wcn36xx {int /*<<< orphan*/  hal_buf; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/ * scan_req; int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_work; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_debugfs_exit (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_deinit (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_ctl_blks (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_mem_pools (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_smd_close (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_smd_stop (struct wcn36xx*) ; 

__attribute__((used)) static void wcn36xx_stop(struct ieee80211_hw *hw)
{
	struct wcn36xx *wcn = hw->priv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac stop\n");

	cancel_work_sync(&wcn->scan_work);

	mutex_lock(&wcn->scan_lock);
	if (wcn->scan_req) {
		struct cfg80211_scan_info scan_info = {
			.aborted = true,
		};

		ieee80211_scan_completed(wcn->hw, &scan_info);
	}
	wcn->scan_req = NULL;
	mutex_unlock(&wcn->scan_lock);

	wcn36xx_debugfs_exit(wcn);
	wcn36xx_smd_stop(wcn);
	wcn36xx_dxe_deinit(wcn);
	wcn36xx_smd_close(wcn);

	wcn36xx_dxe_free_mem_pools(wcn);
	wcn36xx_dxe_free_ctl_blks(wcn);

	kfree(wcn->hal_buf);
}