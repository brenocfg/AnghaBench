#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bcma_drv_cc {int dummy; } ;
struct TYPE_8__ {int radio_ver; int /*<<< orphan*/  channel; } ;
struct b43_wldev {TYPE_4__ phy; int /*<<< orphan*/  wl; TYPE_3__* dev; } ;
struct TYPE_7__ {TYPE_2__* bdev; } ;
struct TYPE_6__ {TYPE_1__* bus; } ;
struct TYPE_5__ {struct bcma_drv_cc drv_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_lcn_afe_set_unset (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_bu_tweaks (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_rev0_baseband_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_tables_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_tx_pwr_ctl_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_2064_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_switch_channel (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_chipco_chipctl_maskset (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_chipco_regctl_maskset (struct bcma_drv_cc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int b43_phy_lcn_op_init(struct b43_wldev *dev)
{
	struct bcma_drv_cc *cc = &dev->dev->bdev->bus->drv_cc;

	b43_phy_set(dev, 0x44a, 0x80);
	b43_phy_mask(dev, 0x44a, 0x7f);
	b43_phy_set(dev, 0x6d1, 0x80);
	b43_phy_write(dev, 0x6d0, 0x7);

	b43_phy_lcn_afe_set_unset(dev);

	b43_phy_write(dev, 0x60a, 0xa0);
	b43_phy_write(dev, 0x46a, 0x19);
	b43_phy_maskset(dev, 0x663, 0xFF00, 0x64);

	b43_phy_lcn_tables_init(dev);

	b43_phy_lcn_rev0_baseband_init(dev);
	b43_phy_lcn_bu_tweaks(dev);

	if (dev->phy.radio_ver == 0x2064)
		b43_radio_2064_init(dev);
	else
		B43_WARN_ON(1);

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_phy_lcn_tx_pwr_ctl_init(dev);

	b43_switch_channel(dev, dev->phy.channel);

	bcma_chipco_regctl_maskset(cc, 0, 0xf, 0x9);
	bcma_chipco_chipctl_maskset(cc, 0, 0, 0x03cddddd);

	/* TODO */

	b43_phy_set(dev, 0x448, 0x4000);
	udelay(100);
	b43_phy_mask(dev, 0x448, ~0x4000);

	/* TODO */

	return 0;
}