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
struct b43legacy_phy {int radio_ver; int radio_rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */

u16 b43legacy_default_txctl1(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;

	if (phy->radio_ver != 0x2050)
		return 0;
	if (phy->radio_rev == 1)
		return 3;
	if (phy->radio_rev < 6)
		return 2;
	if (phy->radio_rev == 8)
		return 1;
	return 0;
}