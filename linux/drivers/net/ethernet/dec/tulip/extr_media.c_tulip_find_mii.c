#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tulip_private {int* phys; int mii_advertise; unsigned int* advertising; size_t default_port; int mii_cnt; TYPE_1__* mtable; scalar_t__ full_duplex; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_mii; } ;

/* Variables and functions */
 int ADVERTISE_ALL ; 
 int ARRAY_SIZE (int*) ; 
 int BMCR_ANENABLE ; 
 unsigned int BMCR_ANRESTART ; 
 unsigned int BMCR_CTST ; 
 unsigned int BMCR_FULLDPLX ; 
 unsigned int BMCR_ISOLATE ; 
 unsigned int BMCR_LOOPBACK ; 
 unsigned int BMCR_PDOWN ; 
 unsigned int BMCR_RESET ; 
 unsigned int BMCR_SPEED100 ; 
 int BMSR_100BASE4 ; 
 int MII_ADVERTISE ; 
 int MII_BMCR ; 
 int MII_BMSR ; 
 int MediaIs100 ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 void* tulip_mdio_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  tulip_mdio_write (struct net_device*,int,int,unsigned int) ; 
 int* tulip_media_cap ; 
 int /*<<< orphan*/  udelay (int) ; 

void tulip_find_mii(struct net_device *dev, int board_idx)
{
	struct tulip_private *tp = netdev_priv(dev);
	int phyn, phy_idx = 0;
	int mii_reg0;
	int mii_advert;
	unsigned int to_advert, new_bmcr, ane_switch;

	/* Find the connected MII xcvrs.
	   Doing this in open() would allow detecting external xcvrs later,
	   but takes much time. */
	for (phyn = 1; phyn <= 32 && phy_idx < ARRAY_SIZE(tp->phys); phyn++) {
		int phy = phyn & 0x1f;
		int mii_status = tulip_mdio_read (dev, phy, MII_BMSR);
		if ((mii_status & 0x8301) == 0x8001 ||
		    ((mii_status & BMSR_100BASE4) == 0 &&
		     (mii_status & 0x7800) != 0)) {
			/* preserve Becker logic, gain indentation level */
		} else {
			continue;
		}

		mii_reg0 = tulip_mdio_read (dev, phy, MII_BMCR);
		mii_advert = tulip_mdio_read (dev, phy, MII_ADVERTISE);
		ane_switch = 0;

		/* if not advertising at all, gen an
		 * advertising value from the capability
		 * bits in BMSR
		 */
		if ((mii_advert & ADVERTISE_ALL) == 0) {
			unsigned int tmpadv = tulip_mdio_read (dev, phy, MII_BMSR);
			mii_advert = ((tmpadv >> 6) & 0x3e0) | 1;
		}

		if (tp->mii_advertise) {
			tp->advertising[phy_idx] =
			to_advert = tp->mii_advertise;
		} else if (tp->advertising[phy_idx]) {
			to_advert = tp->advertising[phy_idx];
		} else {
			tp->advertising[phy_idx] =
			tp->mii_advertise =
			to_advert = mii_advert;
		}

		tp->phys[phy_idx++] = phy;

		pr_info("tulip%d:  MII transceiver #%d config %04x status %04x advertising %04x\n",
			board_idx, phy, mii_reg0, mii_status, mii_advert);

		/* Fixup for DLink with miswired PHY. */
		if (mii_advert != to_advert) {
			pr_debug("tulip%d:  Advertising %04x on PHY %d, previously advertising %04x\n",
				 board_idx, to_advert, phy, mii_advert);
			tulip_mdio_write (dev, phy, 4, to_advert);
		}

		/* Enable autonegotiation: some boards default to off. */
		if (tp->default_port == 0) {
			new_bmcr = mii_reg0 | BMCR_ANENABLE;
			if (new_bmcr != mii_reg0) {
				new_bmcr |= BMCR_ANRESTART;
				ane_switch = 1;
			}
		}
		/* ...or disable nway, if forcing media */
		else {
			new_bmcr = mii_reg0 & ~BMCR_ANENABLE;
			if (new_bmcr != mii_reg0)
				ane_switch = 1;
		}

		/* clear out bits we never want at this point */
		new_bmcr &= ~(BMCR_CTST | BMCR_FULLDPLX | BMCR_ISOLATE |
			      BMCR_PDOWN | BMCR_SPEED100 | BMCR_LOOPBACK |
			      BMCR_RESET);

		if (tp->full_duplex)
			new_bmcr |= BMCR_FULLDPLX;
		if (tulip_media_cap[tp->default_port] & MediaIs100)
			new_bmcr |= BMCR_SPEED100;

		if (new_bmcr != mii_reg0) {
			/* some phys need the ANE switch to
			 * happen before forced media settings
			 * will "take."  However, we write the
			 * same value twice in order not to
			 * confuse the sane phys.
			 */
			if (ane_switch) {
				tulip_mdio_write (dev, phy, MII_BMCR, new_bmcr);
				udelay (10);
			}
			tulip_mdio_write (dev, phy, MII_BMCR, new_bmcr);
		}
	}
	tp->mii_cnt = phy_idx;
	if (tp->mtable && tp->mtable->has_mii && phy_idx == 0) {
		pr_info("tulip%d: ***WARNING***: No MII transceiver found!\n",
			board_idx);
		tp->phys[0] = 1;
	}
}