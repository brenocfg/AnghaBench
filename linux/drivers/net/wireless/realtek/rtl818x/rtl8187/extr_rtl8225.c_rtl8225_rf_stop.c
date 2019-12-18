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
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void rtl8225_rf_stop(struct ieee80211_hw *dev)
{
	rtl8225_write(dev, 0x4, 0x1f);
}