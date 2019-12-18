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
 int mwl8k_cmd_radio_control (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwl8k_cmd_radio_enable(struct ieee80211_hw *hw)
{
	return mwl8k_cmd_radio_control(hw, 1, 0);
}