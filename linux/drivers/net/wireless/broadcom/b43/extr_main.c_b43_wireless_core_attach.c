#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct b43_phy {int do_full_init; int gmode; int type; TYPE_2__* ops; } ;
struct b43_wldev {struct b43_phy phy; int /*<<< orphan*/  restart_work; TYPE_1__* dev; struct b43_wl* wl; } ;
struct b43_wl {struct b43_wldev* current_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* switch_analog ) (struct b43_wldev*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int bus_type; int core_rev; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int B43_BCMA_IOST_2G_PHY ; 
 int B43_BCMA_IOST_5G_PHY ; 
#define  B43_BUS_BCMA 132 
#define  B43_BUS_SSB 131 
#define  B43_PHYTYPE_G 130 
#define  B43_PHYTYPE_HT 129 
#define  B43_PHYTYPE_LP 128 
 int B43_TMSHIGH_HAVE_2GHZ_PHY ; 
 int B43_TMSHIGH_HAVE_5GHZ_PHY ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  BCMA_IOST ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSB_TMSHIGH ; 
 int /*<<< orphan*/  b43_bus_may_powerdown (struct b43_wldev*) ; 
 int b43_bus_powerup (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_chip_reset ; 
 int /*<<< orphan*/  b43_device_disable (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_phy_allocate (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_free (struct b43_wldev*) ; 
 int b43_phy_versioning (struct b43_wldev*) ; 
 int b43_setup_bands (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_supported_bands (struct b43_wldev*,int*,int*) ; 
 int b43_validate_chipaccess (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wireless_core_reset (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43err (struct b43_wl*,char*) ; 
 int /*<<< orphan*/  b43warn (struct b43_wl*,char*) ; 
 int bcma_aread32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssb_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_wireless_core_attach(struct b43_wldev *dev)
{
	struct b43_wl *wl = dev->wl;
	struct b43_phy *phy = &dev->phy;
	int err;
	u32 tmp;
	bool have_2ghz_phy = false, have_5ghz_phy = false;

	/* Do NOT do any device initialization here.
	 * Do it in wireless_core_init() instead.
	 * This function is for gathering basic information about the HW, only.
	 * Also some structs may be set up here. But most likely you want to have
	 * that in core_init(), too.
	 */

	err = b43_bus_powerup(dev, 0);
	if (err) {
		b43err(wl, "Bus powerup failed\n");
		goto out;
	}

	phy->do_full_init = true;

	/* Try to guess supported bands for the first init needs */
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOST);
		have_2ghz_phy = !!(tmp & B43_BCMA_IOST_2G_PHY);
		have_5ghz_phy = !!(tmp & B43_BCMA_IOST_5G_PHY);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		if (dev->dev->core_rev >= 5) {
			tmp = ssb_read32(dev->dev->sdev, SSB_TMSHIGH);
			have_2ghz_phy = !!(tmp & B43_TMSHIGH_HAVE_2GHZ_PHY);
			have_5ghz_phy = !!(tmp & B43_TMSHIGH_HAVE_5GHZ_PHY);
		} else
			B43_WARN_ON(1);
		break;
#endif
	}

	dev->phy.gmode = have_2ghz_phy;
	b43_wireless_core_reset(dev, dev->phy.gmode);

	/* Get the PHY type. */
	err = b43_phy_versioning(dev);
	if (err)
		goto err_powerdown;

	/* Get real info about supported bands */
	b43_supported_bands(dev, &have_2ghz_phy, &have_5ghz_phy);

	/* We don't support 5 GHz on some PHYs yet */
	if (have_5ghz_phy) {
		switch (dev->phy.type) {
		case B43_PHYTYPE_G:
		case B43_PHYTYPE_LP:
		case B43_PHYTYPE_HT:
			b43warn(wl, "5 GHz band is unsupported on this PHY\n");
			have_5ghz_phy = false;
		}
	}

	if (!have_2ghz_phy && !have_5ghz_phy) {
		b43err(wl, "b43 can't support any band on this device\n");
		err = -EOPNOTSUPP;
		goto err_powerdown;
	}

	err = b43_phy_allocate(dev);
	if (err)
		goto err_powerdown;

	dev->phy.gmode = have_2ghz_phy;
	b43_wireless_core_reset(dev, dev->phy.gmode);

	err = b43_validate_chipaccess(dev);
	if (err)
		goto err_phy_free;
	err = b43_setup_bands(dev, have_2ghz_phy, have_5ghz_phy);
	if (err)
		goto err_phy_free;

	/* Now set some default "current_dev" */
	if (!wl->current_dev)
		wl->current_dev = dev;
	INIT_WORK(&dev->restart_work, b43_chip_reset);

	dev->phy.ops->switch_analog(dev, 0);
	b43_device_disable(dev, 0);
	b43_bus_may_powerdown(dev);

out:
	return err;

err_phy_free:
	b43_phy_free(dev);
err_powerdown:
	b43_bus_may_powerdown(dev);
	return err;
}