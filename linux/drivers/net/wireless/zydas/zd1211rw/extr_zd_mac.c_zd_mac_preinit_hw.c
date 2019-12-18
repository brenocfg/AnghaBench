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
typedef  int /*<<< orphan*/  u8 ;
struct zd_mac {int /*<<< orphan*/  chip; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int zd_chip_read_mac_addr_fw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 

int zd_mac_preinit_hw(struct ieee80211_hw *hw)
{
	int r;
	u8 addr[ETH_ALEN];
	struct zd_mac *mac = zd_hw_mac(hw);

	r = zd_chip_read_mac_addr_fw(&mac->chip, addr);
	if (r)
		return r;

	SET_IEEE80211_PERM_ADDR(hw, addr);

	return 0;
}