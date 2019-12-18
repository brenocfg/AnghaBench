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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_cfg80211_vif_event {int /*<<< orphan*/  vif_wq; } ;
struct brcmf_cfg80211_info {struct brcmf_cfg80211_vif_event vif_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  vif_event_equals (struct brcmf_cfg80211_vif_event*,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int brcmf_cfg80211_wait_vif_event(struct brcmf_cfg80211_info *cfg,
				  u8 action, ulong timeout)
{
	struct brcmf_cfg80211_vif_event *event = &cfg->vif_event;

	return wait_event_timeout(event->vif_wq,
				  vif_event_equals(event, action), timeout);
}