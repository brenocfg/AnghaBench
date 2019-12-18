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
struct brcmf_cfg80211_info {int dongle_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_abort_scanning (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_deinit_priv_mem (struct brcmf_cfg80211_info*) ; 

__attribute__((used)) static void wl_deinit_priv(struct brcmf_cfg80211_info *cfg)
{
	cfg->dongle_up = false;	/* dongle down */
	brcmf_abort_scanning(cfg);
	brcmf_deinit_priv_mem(cfg);
}