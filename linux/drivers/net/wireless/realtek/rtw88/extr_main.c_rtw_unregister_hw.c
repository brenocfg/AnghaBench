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
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtw_unset_supported_band (struct ieee80211_hw*,struct rtw_chip_info*) ; 

void rtw_unregister_hw(struct rtw_dev *rtwdev, struct ieee80211_hw *hw)
{
	struct rtw_chip_info *chip = rtwdev->chip;

	ieee80211_unregister_hw(hw);
	rtw_unset_supported_band(hw, chip);
}