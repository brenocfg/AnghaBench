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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _disablegpio (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _resetdigitalprocedure1 (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  disable_analog (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  disable_rfafeandresetbb (struct ieee80211_hw*) ; 

__attribute__((used)) static void carddisable_hwsm(struct ieee80211_hw *hw)
{
	/* ==== RF Off Sequence ==== */
	disable_rfafeandresetbb(hw);
	/* ==== Reset digital sequence   ====== */
	_resetdigitalprocedure1(hw, false);
	/*  ==== Pull GPIO PIN to balance level and LED control ====== */
	_disablegpio(hw);
	/* ==== Disable analog sequence === */
	disable_analog(hw, false);
}