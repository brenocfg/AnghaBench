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
struct wl1251 {int /*<<< orphan*/  monitor_present; } ;
struct ieee80211_conf {int flags; } ;

/* Variables and functions */
 int IEEE80211_CONF_PS ; 

__attribute__((used)) static bool wl1251_can_do_pm(struct ieee80211_conf *conf, struct wl1251 *wl)
{
	return (conf->flags & IEEE80211_CONF_PS) && !wl->monitor_present;
}