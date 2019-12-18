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
struct brcmf_cfg80211_info {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_btcoex_detach (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_free_wiphy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pno_detach (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_deinit_priv (struct brcmf_cfg80211_info*) ; 

void brcmf_cfg80211_detach(struct brcmf_cfg80211_info *cfg)
{
	if (!cfg)
		return;

	brcmf_pno_detach(cfg);
	brcmf_btcoex_detach(cfg);
	wiphy_unregister(cfg->wiphy);
	wl_deinit_priv(cfg);
	brcmf_free_wiphy(cfg->wiphy);
	kfree(cfg);
}