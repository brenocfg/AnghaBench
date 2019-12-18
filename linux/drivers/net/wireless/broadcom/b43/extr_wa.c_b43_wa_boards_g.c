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
struct ssb_sprom {int boardflags_lo; } ;
struct b43_phy {int rev; } ;
struct b43_wldev {TYPE_1__* dev; struct b43_phy phy; } ;
struct TYPE_2__ {scalar_t__ board_vendor; scalar_t__ board_type; int board_rev; struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B43_BFL_EXTLNA ; 
 int B43_BFL_FEM ; 
 int /*<<< orphan*/  B43_OFDMTAB_GAINX ; 
 int /*<<< orphan*/  B43_OFDMTAB_GAINX_R1 ; 
 int /*<<< orphan*/  B43_PHY_EXTG (int) ; 
 int /*<<< orphan*/  B43_PHY_GTABCTL ; 
 int /*<<< orphan*/  B43_PHY_GTABDATA ; 
 scalar_t__ SSB_BOARDVENDOR_BCM ; 
 scalar_t__ SSB_BOARD_BU4306 ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_wa_boards_g(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy *phy = &dev->phy;

	if (dev->dev->board_vendor != SSB_BOARDVENDOR_BCM ||
	    dev->dev->board_type != SSB_BOARD_BU4306 ||
	    dev->dev->board_rev != 0x17) {
		if (phy->rev < 2) {
			b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX_R1, 1, 0x0002);
			b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX_R1, 2, 0x0001);
		} else {
			b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 1, 0x0002);
			b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 2, 0x0001);
			if ((sprom->boardflags_lo & B43_BFL_EXTLNA) &&
			    (phy->rev >= 7)) {
				b43_phy_mask(dev, B43_PHY_EXTG(0x11), 0xF7FF);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0020, 0x0001);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0021, 0x0001);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0022, 0x0001);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0023, 0x0000);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0000, 0x0000);
				b43_ofdmtab_write16(dev, B43_OFDMTAB_GAINX, 0x0003, 0x0002);
			}
		}
	}
	if (sprom->boardflags_lo & B43_BFL_FEM) {
		b43_phy_write(dev, B43_PHY_GTABCTL, 0x3120);
		b43_phy_write(dev, B43_PHY_GTABDATA, 0xC480);
	}
}