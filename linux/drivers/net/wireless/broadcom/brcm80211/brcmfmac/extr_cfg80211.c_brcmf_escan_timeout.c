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
struct timer_list {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  escan_timeout_work; scalar_t__ scan_request; scalar_t__ int_escan_map; struct brcmf_pub* pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 struct brcmf_cfg80211_info* cfg ; 
 int /*<<< orphan*/  escan_timeout ; 
 struct brcmf_cfg80211_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_escan_timeout(struct timer_list *t)
{
	struct brcmf_cfg80211_info *cfg =
			from_timer(cfg, t, escan_timeout);
	struct brcmf_pub *drvr = cfg->pub;

	if (cfg->int_escan_map || cfg->scan_request) {
		bphy_err(drvr, "timer expired\n");
		schedule_work(&cfg->escan_timeout_work);
	}
}