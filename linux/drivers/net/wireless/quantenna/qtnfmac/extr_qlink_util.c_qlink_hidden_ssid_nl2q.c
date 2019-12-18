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
typedef  enum qlink_hidden_ssid { ____Placeholder_qlink_hidden_ssid } qlink_hidden_ssid ;
typedef  enum nl80211_hidden_ssid { ____Placeholder_nl80211_hidden_ssid } nl80211_hidden_ssid ;

/* Variables and functions */
#define  NL80211_HIDDEN_SSID_NOT_IN_USE 130 
#define  NL80211_HIDDEN_SSID_ZERO_CONTENTS 129 
#define  NL80211_HIDDEN_SSID_ZERO_LEN 128 
 int QLINK_HIDDEN_SSID_NOT_IN_USE ; 
 int QLINK_HIDDEN_SSID_ZERO_CONTENTS ; 
 int QLINK_HIDDEN_SSID_ZERO_LEN ; 

enum qlink_hidden_ssid qlink_hidden_ssid_nl2q(enum nl80211_hidden_ssid nl_val)
{
	switch (nl_val) {
	case NL80211_HIDDEN_SSID_ZERO_LEN:
		return QLINK_HIDDEN_SSID_ZERO_LEN;
	case NL80211_HIDDEN_SSID_ZERO_CONTENTS:
		return QLINK_HIDDEN_SSID_ZERO_CONTENTS;
	case NL80211_HIDDEN_SSID_NOT_IN_USE:
	default:
		return QLINK_HIDDEN_SSID_NOT_IN_USE;
	}
}