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
typedef  enum qlink_band { ____Placeholder_qlink_band } qlink_band ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EINVAL ; 
#define  NL80211_BAND_2GHZ 130 
#define  NL80211_BAND_5GHZ 129 
#define  NL80211_BAND_60GHZ 128 
 int QLINK_BAND_2GHZ ; 
 int QLINK_BAND_5GHZ ; 
 int QLINK_BAND_60GHZ ; 

enum qlink_band qlink_utils_band_cfg2q(enum nl80211_band band)
{
	switch (band) {
	case NL80211_BAND_2GHZ:
		return QLINK_BAND_2GHZ;
	case NL80211_BAND_5GHZ:
		return QLINK_BAND_5GHZ;
	case NL80211_BAND_60GHZ:
		return QLINK_BAND_60GHZ;
	default:
		return -EINVAL;
	}
}