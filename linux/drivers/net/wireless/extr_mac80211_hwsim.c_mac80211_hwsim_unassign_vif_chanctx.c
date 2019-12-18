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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_check_chanctx_magic (struct ieee80211_chanctx_conf*) ; 
 int /*<<< orphan*/  hwsim_check_magic (struct ieee80211_vif*) ; 

__attribute__((used)) static void mac80211_hwsim_unassign_vif_chanctx(struct ieee80211_hw *hw,
						struct ieee80211_vif *vif,
						struct ieee80211_chanctx_conf *ctx)
{
	hwsim_check_magic(vif);
	hwsim_check_chanctx_magic(ctx);
}