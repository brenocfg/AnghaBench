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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_force_clear_no_ir_chan (struct wiphy*,struct ieee80211_channel*) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_force_clear_no_ir_freq(struct wiphy *wiphy, u16 center_freq)
{
	struct ieee80211_channel *ch;

	ch = ieee80211_get_channel(wiphy, center_freq);
	if (!ch)
		return;

	ath_force_clear_no_ir_chan(wiphy, ch);
}