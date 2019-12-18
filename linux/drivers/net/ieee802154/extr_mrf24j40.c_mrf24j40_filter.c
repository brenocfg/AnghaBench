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
typedef  int u8 ;
struct mrf24j40 {int /*<<< orphan*/  regmap_short; } ;
struct ieee802154_hw_addr_filt {char* short_addr; char* pan_id; scalar_t__ pan_coord; int /*<<< orphan*/  ieee_addr; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 int BIT_PANCOORD ; 
 unsigned long IEEE802154_AFILT_IEEEADDR_CHANGED ; 
 unsigned long IEEE802154_AFILT_PANC_CHANGED ; 
 unsigned long IEEE802154_AFILT_PANID_CHANGED ; 
 unsigned long IEEE802154_AFILT_SADDR_CHANGED ; 
 scalar_t__ REG_EADR0 ; 
 scalar_t__ REG_PANIDH ; 
 scalar_t__ REG_PANIDL ; 
 int /*<<< orphan*/  REG_RXMCR ; 
 scalar_t__ REG_SADRH ; 
 scalar_t__ REG_SADRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int mrf24j40_filter(struct ieee802154_hw *hw,
			   struct ieee802154_hw_addr_filt *filt,
			   unsigned long changed)
{
	struct mrf24j40 *devrec = hw->priv;

	dev_dbg(printdev(devrec), "filter\n");

	if (changed & IEEE802154_AFILT_SADDR_CHANGED) {
		/* Short Addr */
		u8 addrh, addrl;

		addrh = le16_to_cpu(filt->short_addr) >> 8 & 0xff;
		addrl = le16_to_cpu(filt->short_addr) & 0xff;

		regmap_write(devrec->regmap_short, REG_SADRH, addrh);
		regmap_write(devrec->regmap_short, REG_SADRL, addrl);
		dev_dbg(printdev(devrec),
			"Set short addr to %04hx\n", filt->short_addr);
	}

	if (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) {
		/* Device Address */
		u8 i, addr[8];

		memcpy(addr, &filt->ieee_addr, 8);
		for (i = 0; i < 8; i++)
			regmap_write(devrec->regmap_short, REG_EADR0 + i,
				     addr[i]);

#ifdef DEBUG
		pr_debug("Set long addr to: ");
		for (i = 0; i < 8; i++)
			pr_debug("%02hhx ", addr[7 - i]);
		pr_debug("\n");
#endif
	}

	if (changed & IEEE802154_AFILT_PANID_CHANGED) {
		/* PAN ID */
		u8 panidl, panidh;

		panidh = le16_to_cpu(filt->pan_id) >> 8 & 0xff;
		panidl = le16_to_cpu(filt->pan_id) & 0xff;
		regmap_write(devrec->regmap_short, REG_PANIDH, panidh);
		regmap_write(devrec->regmap_short, REG_PANIDL, panidl);

		dev_dbg(printdev(devrec), "Set PANID to %04hx\n", filt->pan_id);
	}

	if (changed & IEEE802154_AFILT_PANC_CHANGED) {
		/* Pan Coordinator */
		u8 val;
		int ret;

		if (filt->pan_coord)
			val = BIT_PANCOORD;
		else
			val = 0;
		ret = regmap_update_bits(devrec->regmap_short, REG_RXMCR,
					 BIT_PANCOORD, val);
		if (ret)
			return ret;

		/* REG_SLOTTED is maintained as default (unslotted/CSMA-CA).
		 * REG_ORDER is maintained as default (no beacon/superframe).
		 */

		dev_dbg(printdev(devrec), "Set Pan Coord to %s\n",
			filt->pan_coord ? "on" : "off");
	}

	return 0;
}