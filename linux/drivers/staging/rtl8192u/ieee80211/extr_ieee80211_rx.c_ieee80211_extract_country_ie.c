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
struct ieee80211_network {scalar_t__ CountryIeLen; int /*<<< orphan*/  CountryIeBuf; } ;
struct ieee80211_info_element {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_COUNTRY_IE_VALID (struct ieee80211_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct ieee80211_device*) ; 
 scalar_t__ IS_EQUAL_CIE_SRC (struct ieee80211_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CIE_WATCHDOG (struct ieee80211_device*) ; 
 int /*<<< orphan*/  dot11d_update_country_ie (struct ieee80211_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void ieee80211_extract_country_ie(
	struct ieee80211_device *ieee,
	struct ieee80211_info_element *info_element,
	struct ieee80211_network *network,
	u8 *addr2
)
{
	if (IS_DOT11D_ENABLE(ieee)) {
		if (info_element->len != 0) {
			memcpy(network->CountryIeBuf, info_element->data, info_element->len);
			network->CountryIeLen = info_element->len;

			if (!IS_COUNTRY_IE_VALID(ieee)) {
				dot11d_update_country_ie(ieee, addr2, info_element->len, info_element->data);
			}
		}

		//
		// 070305, rcnjko: I update country IE watch dog here because
		// some AP (e.g. Cisco 1242) don't include country IE in their
		// probe response frame.
		//
		if (IS_EQUAL_CIE_SRC(ieee, addr2)) {
			UPDATE_CIE_WATCHDOG(ieee);
		}
	}

}