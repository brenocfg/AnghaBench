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
struct rtl818x_rf_ops {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl818x_rf_ops const rtl8225se_ops ; 

const struct rtl818x_rf_ops *rtl8187se_detect_rf(struct ieee80211_hw *dev)
{
	return &rtl8225se_ops;
}