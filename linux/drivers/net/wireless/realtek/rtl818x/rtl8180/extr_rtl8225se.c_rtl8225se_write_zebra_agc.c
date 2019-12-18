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
 int* ZEBRA_AGC ; 
 int /*<<< orphan*/  rtl8225se_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void rtl8225se_write_zebra_agc(struct ieee80211_hw *dev)
{
	int i;

	for (i = 0; i < 128; i++) {
		rtl8225se_write_phy_ofdm(dev, 0xF, ZEBRA_AGC[i]);
		rtl8225se_write_phy_ofdm(dev, 0xE, i+0x80);
		rtl8225se_write_phy_ofdm(dev, 0xE, 0);
	}
}