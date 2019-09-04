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
struct ssb_sprom {int /*<<< orphan*/ * il0mac; int /*<<< orphan*/  et2phyaddr; int /*<<< orphan*/  et2mdcport; int /*<<< orphan*/ * et2mac; int /*<<< orphan*/  et1phyaddr; int /*<<< orphan*/  et1mdcport; int /*<<< orphan*/ * et1mac; int /*<<< orphan*/  et0phyaddr; int /*<<< orphan*/  et0mdcport; int /*<<< orphan*/ * et0mac; } ;

/* Variables and functions */
 int bcm47xx_increase_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bcm47xx_is_valid_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_addr_used ; 
 int /*<<< orphan*/  nvram_read_macaddr (char const*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvram_read_u8 (char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm47xx_fill_sprom_ethernet(struct ssb_sprom *sprom,
					const char *prefix, bool fallback)
{
	bool fb = fallback;

	nvram_read_macaddr(prefix, "et0macaddr", sprom->et0mac, fallback);
	nvram_read_u8(prefix, NULL, "et0mdcport", &sprom->et0mdcport, 0,
		      fallback);
	nvram_read_u8(prefix, NULL, "et0phyaddr", &sprom->et0phyaddr, 0,
		      fallback);

	nvram_read_macaddr(prefix, "et1macaddr", sprom->et1mac, fallback);
	nvram_read_u8(prefix, NULL, "et1mdcport", &sprom->et1mdcport, 0,
		      fallback);
	nvram_read_u8(prefix, NULL, "et1phyaddr", &sprom->et1phyaddr, 0,
		      fallback);

	nvram_read_macaddr(prefix, "et2macaddr", sprom->et2mac, fb);
	nvram_read_u8(prefix, NULL, "et2mdcport", &sprom->et2mdcport, 0, fb);
	nvram_read_u8(prefix, NULL, "et2phyaddr", &sprom->et2phyaddr, 0, fb);

	nvram_read_macaddr(prefix, "macaddr", sprom->il0mac, fallback);
	nvram_read_macaddr(prefix, "il0macaddr", sprom->il0mac, fallback);

	/* The address prefix 00:90:4C is used by Broadcom in their initial
	 * configuration. When a mac address with the prefix 00:90:4C is used
	 * all devices from the same series are sharing the same mac address.
	 * To prevent mac address collisions we replace them with a mac address
	 * based on the base address.
	 */
	if (!bcm47xx_is_valid_mac(sprom->il0mac)) {
		u8 mac[6];

		nvram_read_macaddr(NULL, "et0macaddr", mac, false);
		if (bcm47xx_is_valid_mac(mac)) {
			int err = bcm47xx_increase_mac_addr(mac, mac_addr_used);

			if (!err) {
				ether_addr_copy(sprom->il0mac, mac);
				mac_addr_used++;
			}
		}
	}
}