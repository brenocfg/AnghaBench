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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_device {int dummy; } ;
struct b43legacy_wldev {struct ssb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_TMSLOW_GMODE ; 
 int /*<<< orphan*/  B43legacy_TMSLOW_PHYRESET ; 
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int /*<<< orphan*/  SSB_TMSLOW_FGC ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_put_phy_into_reset(struct b43legacy_wldev *dev)
{
	struct ssb_device *sdev = dev->dev;
	u32 tmslow;

	tmslow = ssb_read32(sdev, SSB_TMSLOW);
	tmslow &= ~B43legacy_TMSLOW_GMODE;
	tmslow |= B43legacy_TMSLOW_PHYRESET;
	tmslow |= SSB_TMSLOW_FGC;
	ssb_write32(sdev, SSB_TMSLOW, tmslow);
	msleep(1);

	tmslow = ssb_read32(sdev, SSB_TMSLOW);
	tmslow &= ~SSB_TMSLOW_FGC;
	tmslow |= B43legacy_TMSLOW_PHYRESET;
	ssb_write32(sdev, SSB_TMSLOW, tmslow);
	msleep(1);
}