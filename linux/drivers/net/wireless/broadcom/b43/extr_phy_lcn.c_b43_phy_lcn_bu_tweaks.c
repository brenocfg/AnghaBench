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
struct TYPE_6__ {int rev; } ;
struct b43_wldev {TYPE_3__ phy; TYPE_2__* dev; } ;
struct TYPE_5__ {TYPE_1__* bus_sprom; } ;
struct TYPE_4__ {int board_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_phy_lcn_clear_tx_power_offsets (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_phy_lcn_bu_tweaks(struct b43_wldev *dev)
{
	b43_phy_set(dev, 0x805, 0x1);

	b43_phy_maskset(dev, 0x42f, ~0x7, 0x3);
	b43_phy_maskset(dev, 0x030, ~0x7, 0x3);

	b43_phy_write(dev, 0x414, 0x1e10);
	b43_phy_write(dev, 0x415, 0x0640);

	b43_phy_maskset(dev, 0x4df, (u16) ~0xff00, 0xf700);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_write(dev, 0x44a, 0x80);

	b43_phy_maskset(dev, 0x434, ~0xff, 0xfd);
	b43_phy_maskset(dev, 0x420, ~0xff, 0x10);

	if (dev->dev->bus_sprom->board_rev >= 0x1204)
		b43_radio_set(dev, 0x09b, 0xf0);

	b43_phy_write(dev, 0x7d6, 0x0902);

	b43_phy_maskset(dev, 0x429, ~0xf, 0x9);
	b43_phy_maskset(dev, 0x429, ~(0x3f << 4), 0xe << 4);

	if (dev->phy.rev == 1) {
		b43_phy_maskset(dev, 0x423, ~0xff, 0x46);
		b43_phy_maskset(dev, 0x411, ~0xff, 1);
		b43_phy_set(dev, 0x434, 0xff); /* FIXME: update to wl */

		/* TODO: wl operates on PHY 0x416, brcmsmac is outdated here */

		b43_phy_maskset(dev, 0x656, ~0xf, 2);
		b43_phy_set(dev, 0x44d, 4);

		b43_radio_set(dev, 0x0f7, 0x4);
		b43_radio_mask(dev, 0x0f1, ~0x3);
		b43_radio_maskset(dev, 0x0f2, ~0xf8, 0x90);
		b43_radio_maskset(dev, 0x0f3, ~0x3, 0x2);
		b43_radio_maskset(dev, 0x0f3, ~0xf0, 0xa0);

		b43_radio_set(dev, 0x11f, 0x2);

		b43_phy_lcn_clear_tx_power_offsets(dev);

		/* TODO: something more? */
	}
}