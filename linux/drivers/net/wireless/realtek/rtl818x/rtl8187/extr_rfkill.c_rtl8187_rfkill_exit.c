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
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wiphy_rfkill_stop_polling (int /*<<< orphan*/ ) ; 

void rtl8187_rfkill_exit(struct ieee80211_hw *hw)
{
	wiphy_rfkill_stop_polling(hw->wiphy);
}