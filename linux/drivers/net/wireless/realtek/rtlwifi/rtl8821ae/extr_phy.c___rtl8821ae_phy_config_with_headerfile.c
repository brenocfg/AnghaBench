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
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ COND_ELSE ; 
 scalar_t__ COND_ENDIF ; 
 scalar_t__ _rtl8821ae_check_positive (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static bool
__rtl8821ae_phy_config_with_headerfile(struct ieee80211_hw *hw,
				       u32 *array_table, u16 arraylen,
				       void (*set_reg)(struct ieee80211_hw *hw,
						       u32 regaddr, u32 data))
{
	#define COND_ELSE  2
	#define COND_ENDIF 3

	int i = 0;
	u8 cond;
	bool matched = true, skipped = false;

	while ((i + 1) < arraylen) {
		u32 v1 = array_table[i];
		u32 v2 = array_table[i + 1];

		if (v1 & (BIT(31) | BIT(30))) {/*positive & negative condition*/
			if (v1 & BIT(31)) {/* positive condition*/
				cond  = (u8)((v1 & (BIT(29) | BIT(28))) >> 28);
				if (cond == COND_ENDIF) {/*end*/
					matched = true;
					skipped = false;
				} else if (cond == COND_ELSE) /*else*/
					matched = skipped ? false : true;
				else {/*if , else if*/
					if (skipped) {
						matched = false;
					} else {
						if (_rtl8821ae_check_positive(
								hw, v1, v2)) {
							matched = true;
							skipped = true;
						} else {
							matched = false;
							skipped = false;
						}
					}
				}
			} else if (v1 & BIT(30)) { /*negative condition*/
			/*do nothing*/
			}
		} else {
			if (matched)
				set_reg(hw, v1, v2);
		}
		i = i + 2;
	}

	return true;
}