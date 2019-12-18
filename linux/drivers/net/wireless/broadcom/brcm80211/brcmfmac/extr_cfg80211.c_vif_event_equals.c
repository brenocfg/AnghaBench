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
typedef  scalar_t__ u8 ;
struct brcmf_cfg80211_vif_event {scalar_t__ action; int /*<<< orphan*/  vif_event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool vif_event_equals(struct brcmf_cfg80211_vif_event *event,
				    u8 action)
{
	u8 evt_action;

	spin_lock(&event->vif_event_lock);
	evt_action = event->action;
	spin_unlock(&event->vif_event_lock);
	return evt_action == action;
}