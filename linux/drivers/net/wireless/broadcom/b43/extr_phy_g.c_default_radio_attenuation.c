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
struct b43_phy {int radio_ver; int /*<<< orphan*/  type; int /*<<< orphan*/  radio_rev; } ;
struct b43_wldev {struct b43_bus_dev* dev; struct b43_phy phy; } ;
struct b43_rfatt {int with_padmix; int att; } ;
struct b43_bus_dev {scalar_t__ board_vendor; scalar_t__ board_type; int board_rev; int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHYTYPE_G ; 
 scalar_t__ SSB_BOARDVENDOR_BCM ; 
 scalar_t__ SSB_BOARD_BCM4309G ; 
 scalar_t__ SSB_BOARD_BU4306 ; 

__attribute__((used)) static void default_radio_attenuation(struct b43_wldev *dev,
				      struct b43_rfatt *rf)
{
	struct b43_bus_dev *bdev = dev->dev;
	struct b43_phy *phy = &dev->phy;

	rf->with_padmix = false;

	if (dev->dev->board_vendor == SSB_BOARDVENDOR_BCM &&
	    dev->dev->board_type == SSB_BOARD_BCM4309G) {
		if (dev->dev->board_rev < 0x43) {
			rf->att = 2;
			return;
		} else if (dev->dev->board_rev < 0x51) {
			rf->att = 3;
			return;
		}
	}

	switch (phy->radio_ver) {
	case 0x2053:
		switch (phy->radio_rev) {
		case 1:
			rf->att = 6;
			return;
		}
		break;
	case 0x2050:
		switch (phy->radio_rev) {
		case 0:
			rf->att = 5;
			return;
		case 1:
			if (phy->type == B43_PHYTYPE_G) {
				if (bdev->board_vendor == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 3;
				else if (bdev->board_vendor ==
					 SSB_BOARDVENDOR_BCM
					 && bdev->board_type ==
					 SSB_BOARD_BU4306)
					rf->att = 3;
				else
					rf->att = 1;
			} else {
				if (bdev->board_vendor == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 7;
				else
					rf->att = 6;
			}
			return;
		case 2:
			if (phy->type == B43_PHYTYPE_G) {
				if (bdev->board_vendor == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 3;
				else if (bdev->board_vendor ==
					 SSB_BOARDVENDOR_BCM
					 && bdev->board_type ==
					 SSB_BOARD_BU4306)
					rf->att = 5;
				else if (bdev->chip_id == 0x4320)
					rf->att = 4;
				else
					rf->att = 3;
			} else
				rf->att = 6;
			return;
		case 3:
			rf->att = 5;
			return;
		case 4:
		case 5:
			rf->att = 1;
			return;
		case 6:
		case 7:
			rf->att = 5;
			return;
		case 8:
			rf->att = 0xA;
			rf->with_padmix = true;
			return;
		case 9:
		default:
			rf->att = 5;
			return;
		}
	}
	rf->att = 5;
}