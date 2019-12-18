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
 int /*<<< orphan*/  rtl8180_write_phy (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  write_max2820 (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max2820_rf_stop(struct ieee80211_hw *dev)
{
	rtl8180_write_phy(dev, 3, 0x8);
	write_max2820(dev, 1, 0);
}