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
struct wcn36xx_hal_scan_offload_ind {int type; } ;
struct wcn36xx {int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  scan_aborted; int /*<<< orphan*/ * scan_req; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
#define  WCN36XX_HAL_SCAN_IND_COMPLETED 134 
#define  WCN36XX_HAL_SCAN_IND_DEQUEUED 133 
#define  WCN36XX_HAL_SCAN_IND_FAILED 132 
#define  WCN36XX_HAL_SCAN_IND_FOREIGN_CHANNEL 131 
#define  WCN36XX_HAL_SCAN_IND_PREEMPTED 130 
#define  WCN36XX_HAL_SCAN_IND_RESTARTED 129 
#define  WCN36XX_HAL_SCAN_IND_STARTED 128 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,...) ; 

__attribute__((used)) static int wcn36xx_smd_hw_scan_ind(struct wcn36xx *wcn, void *buf, size_t len)
{
	struct wcn36xx_hal_scan_offload_ind *rsp = buf;
	struct cfg80211_scan_info scan_info = {};

	if (len != sizeof(*rsp)) {
		wcn36xx_warn("Corrupted delete scan indication\n");
		return -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAL, "scan indication (type %x)\n", rsp->type);

	switch (rsp->type) {
	case WCN36XX_HAL_SCAN_IND_FAILED:
	case WCN36XX_HAL_SCAN_IND_DEQUEUED:
		scan_info.aborted = true;
		/* fall through */
	case WCN36XX_HAL_SCAN_IND_COMPLETED:
		mutex_lock(&wcn->scan_lock);
		wcn->scan_req = NULL;
		if (wcn->scan_aborted)
			scan_info.aborted = true;
		mutex_unlock(&wcn->scan_lock);
		ieee80211_scan_completed(wcn->hw, &scan_info);
		break;
	case WCN36XX_HAL_SCAN_IND_STARTED:
	case WCN36XX_HAL_SCAN_IND_FOREIGN_CHANNEL:
	case WCN36XX_HAL_SCAN_IND_PREEMPTED:
	case WCN36XX_HAL_SCAN_IND_RESTARTED:
		break;
	default:
		wcn36xx_warn("Unknown scan indication type %x\n", rsp->type);
	}

	return 0;
}