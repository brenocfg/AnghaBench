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
struct rtllib_network {scalar_t__ CountryIeLen; int /*<<< orphan*/  ssid; int /*<<< orphan*/  CountryIeBuf; } ;
struct rtllib_info_element {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtllib_device {int /*<<< orphan*/  dev; scalar_t__ FirstIe_InScan; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_COUNTRY_IE_VALID (struct rtllib_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct rtllib_device*) ; 
 scalar_t__ IS_EQUAL_CIE_SRC (struct rtllib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CIE_WATCHDOG (struct rtllib_device*) ; 
 int /*<<< orphan*/  dot11d_update_country (struct rtllib_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtllib_act_scanning (struct rtllib_device*,int) ; 

__attribute__((used)) static inline void rtllib_extract_country_ie(
	struct rtllib_device *ieee,
	struct rtllib_info_element *info_element,
	struct rtllib_network *network,
	u8 *addr2)
{
	if (IS_DOT11D_ENABLE(ieee)) {
		if (info_element->len != 0) {
			memcpy(network->CountryIeBuf, info_element->data,
			       info_element->len);
			network->CountryIeLen = info_element->len;

			if (!IS_COUNTRY_IE_VALID(ieee)) {
				if (rtllib_act_scanning(ieee, false) &&
				    ieee->FirstIe_InScan)
					netdev_info(ieee->dev,
						    "Received beacon ContryIE, SSID: <%s>\n",
						    network->ssid);
				dot11d_update_country(ieee, addr2,
						       info_element->len,
						       info_element->data);
			}
		}

		if (IS_EQUAL_CIE_SRC(ieee, addr2))
			UPDATE_CIE_WATCHDOG(ieee);
	}
}