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
struct brcmf_cfg80211_info {int pwr_save; int dongle_up; int /*<<< orphan*/  vif_disabled; int /*<<< orphan*/  conf; int /*<<< orphan*/  usr_sync; int /*<<< orphan*/ * scan_request; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_init_conf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_init_escan (struct brcmf_cfg80211_info*) ; 
 scalar_t__ brcmf_init_priv_mem (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_register_event_handlers (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 wl_init_priv(struct brcmf_cfg80211_info *cfg)
{
	s32 err = 0;

	cfg->scan_request = NULL;
	cfg->pwr_save = true;
	cfg->dongle_up = false;		/* dongle is not up yet */
	err = brcmf_init_priv_mem(cfg);
	if (err)
		return err;
	brcmf_register_event_handlers(cfg);
	mutex_init(&cfg->usr_sync);
	brcmf_init_escan(cfg);
	brcmf_init_conf(cfg->conf);
	init_completion(&cfg->vif_disabled);
	return err;
}