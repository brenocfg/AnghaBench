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
typedef  scalar_t__ u32 ;
struct cfg80211_scan_request {int dummy; } ;
struct brcmf_if {TYPE_2__* drvr; } ;
struct TYPE_3__ {int /*<<< orphan*/  run; } ;
struct brcmf_cfg80211_info {scalar_t__ int_escan_map; int /*<<< orphan*/  scan_status; TYPE_1__ escan_info; } ;
struct TYPE_4__ {struct brcmf_cfg80211_info* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SCAN_STATUS_BUSY ; 
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  brcmf_abort_scanning (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int brcmf_do_escan (struct brcmf_if*,struct cfg80211_scan_request*) ; 
 int /*<<< orphan*/  brcmf_run_escan ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_start_internal_escan(struct brcmf_if *ifp, u32 fwmap,
				      struct cfg80211_scan_request *request)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	int err;

	if (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) {
		if (cfg->int_escan_map)
			brcmf_dbg(SCAN, "aborting internal scan: map=%u\n",
				  cfg->int_escan_map);
		/* Abort any on-going scan */
		brcmf_abort_scanning(cfg);
	}

	brcmf_dbg(SCAN, "start internal scan: map=%u\n", fwmap);
	set_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cfg->escan_info.run = brcmf_run_escan;
	err = brcmf_do_escan(ifp, request);
	if (err) {
		clear_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
		return err;
	}
	cfg->int_escan_map = fwmap;
	return 0;
}