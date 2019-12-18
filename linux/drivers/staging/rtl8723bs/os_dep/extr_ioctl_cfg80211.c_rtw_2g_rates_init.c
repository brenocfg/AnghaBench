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
struct ieee80211_rate {int dummy; } ;

/* Variables and functions */
 int RTW_G_RATES_NUM ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_rate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_g_rates ; 

__attribute__((used)) static void rtw_2g_rates_init(struct ieee80211_rate *rates)
{
	memcpy(rates, rtw_g_rates,
		sizeof(struct ieee80211_rate)*RTW_G_RATES_NUM
	);
}