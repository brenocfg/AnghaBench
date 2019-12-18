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
struct b43legacy_wldev {TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_HWENABLED_HI ; 
 int B43legacy_MMIO_RADIO_HWENABLED_HI_MASK ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_HWENABLED_LO ; 
 int B43legacy_MMIO_RADIO_HWENABLED_LO_MASK ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 

bool b43legacy_is_hw_radio_enabled(struct b43legacy_wldev *dev)
{
	if (dev->dev->id.revision >= 3) {
		if (!(b43legacy_read32(dev, B43legacy_MMIO_RADIO_HWENABLED_HI)
		      & B43legacy_MMIO_RADIO_HWENABLED_HI_MASK))
			return true;
	} else {
		/* To prevent CPU fault on PPC, do not read a register
		 * unless the interface is started; however, on resume
		 * for hibernation, this routine is entered early. When
		 * that happens, unconditionally return TRUE.
		 */
		if (b43legacy_status(dev) < B43legacy_STAT_STARTED)
			return true;
		if (b43legacy_read16(dev, B43legacy_MMIO_RADIO_HWENABLED_LO)
		    & B43legacy_MMIO_RADIO_HWENABLED_LO_MASK)
			return true;
	}
	return false;
}