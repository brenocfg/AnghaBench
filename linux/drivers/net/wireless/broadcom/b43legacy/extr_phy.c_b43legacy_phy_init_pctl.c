#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct b43legacy_phy {scalar_t__ type; int savedpctlreg; int rev; int radio_ver; int bbatt; int rfatt; int txctl1; int radio_rev; scalar_t__ manual_txpower_control; int /*<<< orphan*/  gmode; } ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {TYPE_1__ boardinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 scalar_t__ B43legacy_PHYTYPE_B ; 
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int /*<<< orphan*/  B43legacy_PHY_G_PCTL ; 
 int /*<<< orphan*/  b43legacy_dummy_transmission (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_clear_tssi (struct b43legacy_wldev*) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_set_txpower_bg (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 scalar_t__ is_bcm_board_vendor (struct b43legacy_wldev*) ; 

__attribute__((used)) static void b43legacy_phy_init_pctl(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 saved_batt = 0;
	u16 saved_ratt = 0;
	u16 saved_txctl1 = 0;
	int must_reset_txpower = 0;

	B43legacy_BUG_ON(!(phy->type == B43legacy_PHYTYPE_B ||
			  phy->type == B43legacy_PHYTYPE_G));
	if (is_bcm_board_vendor(dev) &&
	    (dev->dev->bus->boardinfo.type == 0x0416))
		return;

	b43legacy_phy_write(dev, 0x0028, 0x8018);
	b43legacy_write16(dev, 0x03E6, b43legacy_read16(dev, 0x03E6) & 0xFFDF);

	if (phy->type == B43legacy_PHYTYPE_G) {
		if (!phy->gmode)
			return;
		b43legacy_phy_write(dev, 0x047A, 0xC111);
	}
	if (phy->savedpctlreg != 0xFFFF)
		return;
#ifdef CONFIG_B43LEGACY_DEBUG
	if (phy->manual_txpower_control)
		return;
#endif

	if (phy->type == B43legacy_PHYTYPE_B &&
	    phy->rev >= 2 &&
	    phy->radio_ver == 0x2050)
		b43legacy_radio_write16(dev, 0x0076,
					b43legacy_radio_read16(dev, 0x0076)
					| 0x0084);
	else {
		saved_batt = phy->bbatt;
		saved_ratt = phy->rfatt;
		saved_txctl1 = phy->txctl1;
		if ((phy->radio_rev >= 6) && (phy->radio_rev <= 8)
		    && /*FIXME: incomplete specs for 5 < revision < 9 */ 0)
			b43legacy_radio_set_txpower_bg(dev, 0xB, 0x1F, 0);
		else
			b43legacy_radio_set_txpower_bg(dev, 0xB, 9, 0);
		must_reset_txpower = 1;
	}
	b43legacy_dummy_transmission(dev);

	phy->savedpctlreg = b43legacy_phy_read(dev, B43legacy_PHY_G_PCTL);

	if (must_reset_txpower)
		b43legacy_radio_set_txpower_bg(dev, saved_batt, saved_ratt,
					       saved_txctl1);
	else
		b43legacy_radio_write16(dev, 0x0076, b43legacy_radio_read16(dev,
					0x0076) & 0xFF7B);
	b43legacy_radio_clear_tssi(dev);
}