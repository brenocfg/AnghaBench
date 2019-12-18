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
typedef  int u16 ;
struct b43legacy_phy {int type; int radio_ver; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_CONTROL ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_DATA_LOW ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

u16 b43legacy_radio_read16(struct b43legacy_wldev *dev, u16 offset)
{
	struct b43legacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
		if (phy->radio_ver == 0x2053) {
			if (offset < 0x70)
				offset += 0x80;
			else if (offset < 0x80)
				offset += 0x70;
		} else if (phy->radio_ver == 0x2050)
			offset |= 0x80;
		else
			B43legacy_WARN_ON(1);
		break;
	case B43legacy_PHYTYPE_G:
		offset |= 0x80;
		break;
	default:
		B43legacy_BUG_ON(1);
	}

	b43legacy_write16(dev, B43legacy_MMIO_RADIO_CONTROL, offset);
	return b43legacy_read16(dev, B43legacy_MMIO_RADIO_DATA_LOW);
}