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
typedef  int u32 ;
struct TYPE_2__ {int gmode; } ;
struct b43legacy_wldev {TYPE_1__ phy; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int B43legacy_MACCTL_GMODE ; 
 int B43legacy_MACCTL_IHR_ENABLED ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int B43legacy_TMSLOW_GMODE ; 
 int B43legacy_TMSLOW_PHYCLKEN ; 
 int B43legacy_TMSLOW_PHYRESET ; 
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int SSB_TMSLOW_FGC ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_switch_analog (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ssb_device_enable (int /*<<< orphan*/ ,int) ; 
 int ssb_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void b43legacy_wireless_core_reset(struct b43legacy_wldev *dev, u32 flags)
{
	u32 tmslow;
	u32 macctl;

	flags |= B43legacy_TMSLOW_PHYCLKEN;
	flags |= B43legacy_TMSLOW_PHYRESET;
	ssb_device_enable(dev->dev, flags);
	msleep(2); /* Wait for the PLL to turn on. */

	/* Now take the PHY out of Reset again */
	tmslow = ssb_read32(dev->dev, SSB_TMSLOW);
	tmslow |= SSB_TMSLOW_FGC;
	tmslow &= ~B43legacy_TMSLOW_PHYRESET;
	ssb_write32(dev->dev, SSB_TMSLOW, tmslow);
	ssb_read32(dev->dev, SSB_TMSLOW); /* flush */
	msleep(1);
	tmslow &= ~SSB_TMSLOW_FGC;
	ssb_write32(dev->dev, SSB_TMSLOW, tmslow);
	ssb_read32(dev->dev, SSB_TMSLOW); /* flush */
	msleep(1);

	/* Turn Analog ON */
	b43legacy_switch_analog(dev, 1);

	macctl = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_GMODE;
	if (flags & B43legacy_TMSLOW_GMODE) {
		macctl |= B43legacy_MACCTL_GMODE;
		dev->phy.gmode = true;
	} else
		dev->phy.gmode = false;
	macctl |= B43legacy_MACCTL_IHR_ENABLED;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, macctl);
}