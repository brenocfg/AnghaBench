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
struct escan_info {scalar_t__ (* run ) (struct brcmf_cfg80211_info*,struct brcmf_if*,struct cfg80211_scan_request*) ;scalar_t__ escan_buf; int /*<<< orphan*/  escan_state; int /*<<< orphan*/  wiphy; struct brcmf_if* ifp; } ;
struct cfg80211_scan_request {int dummy; } ;
struct brcmf_scan_results {int /*<<< orphan*/  buflen; scalar_t__ count; scalar_t__ version; } ;
struct brcmf_if {TYPE_1__* drvr; } ;
struct brcmf_cfg80211_info {struct escan_info escan_info; int /*<<< orphan*/  wiphy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct brcmf_cfg80211_info* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  WL_ESCAN_RESULTS_FIXED_SIZE ; 
 int /*<<< orphan*/  WL_ESCAN_STATE_SCANNING ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_scan_config_mpc (struct brcmf_if*,int) ; 
 scalar_t__ stub1 (struct brcmf_cfg80211_info*,struct brcmf_if*,struct cfg80211_scan_request*) ; 

__attribute__((used)) static s32
brcmf_do_escan(struct brcmf_if *ifp, struct cfg80211_scan_request *request)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	s32 err;
	struct brcmf_scan_results *results;
	struct escan_info *escan = &cfg->escan_info;

	brcmf_dbg(SCAN, "Enter\n");
	escan->ifp = ifp;
	escan->wiphy = cfg->wiphy;
	escan->escan_state = WL_ESCAN_STATE_SCANNING;

	brcmf_scan_config_mpc(ifp, 0);
	results = (struct brcmf_scan_results *)cfg->escan_info.escan_buf;
	results->version = 0;
	results->count = 0;
	results->buflen = WL_ESCAN_RESULTS_FIXED_SIZE;

	err = escan->run(cfg, ifp, request);
	if (err)
		brcmf_scan_config_mpc(ifp, 1);
	return err;
}