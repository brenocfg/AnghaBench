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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_addr_delay (int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl_rfreg_delay(struct ieee80211_hw *hw, enum radio_path rfpath, u32 addr,
		     u32 mask, u32 data)
{
	if (addr >= 0xf9 && addr <= 0xfe) {
		rtl_addr_delay(addr);
	} else {
		rtl_set_rfreg(hw, rfpath, addr, mask, data);
		udelay(1);
	}
}