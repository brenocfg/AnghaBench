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
 int* RF_GAIN_TABLE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8187se_rf_writereg (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void rtl8187se_write_rf_gain(struct ieee80211_hw *dev)
{
	int i;

	for (i = 0; i <= 36; i++) {
		rtl8187se_rf_writereg(dev, 0x01, i); mdelay(1);
		rtl8187se_rf_writereg(dev, 0x02, RF_GAIN_TABLE[i]); mdelay(1);
	}
}