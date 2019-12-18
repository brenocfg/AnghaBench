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
struct pda_country {scalar_t__ flags; int /*<<< orphan*/  alpha2; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 scalar_t__ PDR_COUNTRY_CERT_CODE_PSEUDO ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  regulatory_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void p54_parse_default_country(struct ieee80211_hw *dev,
				      void *data, int len)
{
	struct pda_country *country;

	if (len != sizeof(*country)) {
		wiphy_err(dev->wiphy,
			  "found possible invalid default country eeprom entry. (entry size: %d)\n",
			  len);

		print_hex_dump_bytes("country:", DUMP_PREFIX_NONE,
				     data, len);

		wiphy_err(dev->wiphy, "please report this issue.\n");
		return;
	}

	country = (struct pda_country *) data;
	if (country->flags == PDR_COUNTRY_CERT_CODE_PSEUDO)
		regulatory_hint(dev->wiphy, country->alpha2);
	else {
		/* TODO:
		 * write a shared/common function that converts
		 * "Regulatory domain codes" (802.11-2007 14.8.2.2)
		 * into ISO/IEC 3166-1 alpha2 for regulatory_hint.
		 */
	}
}