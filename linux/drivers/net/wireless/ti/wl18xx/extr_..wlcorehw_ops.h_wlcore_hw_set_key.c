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
struct wl1271 {TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_2__ {int (* set_key ) (struct wl1271*,int,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (struct wl1271*,int,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static inline int
wlcore_hw_set_key(struct wl1271 *wl, enum set_key_cmd cmd,
		  struct ieee80211_vif *vif,
		  struct ieee80211_sta *sta,
		  struct ieee80211_key_conf *key_conf)
{
	if (!wl->ops->set_key)
		BUG_ON(1);

	return wl->ops->set_key(wl, cmd, vif, sta, key_conf);
}