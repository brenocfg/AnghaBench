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
typedef  int u16 ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 

__attribute__((used)) static int p54_get_band_from_freq(u16 freq)
{
	/* FIXME: sync these values with the 802.11 spec */

	if ((freq >= 2412) && (freq <= 2484))
		return NL80211_BAND_2GHZ;

	if ((freq >= 4920) && (freq <= 5825))
		return NL80211_BAND_5GHZ;

	return -1;
}