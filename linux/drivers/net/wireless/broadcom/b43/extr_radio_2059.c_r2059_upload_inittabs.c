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
typedef  scalar_t__ u16 ;
struct b43_phy {int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__**) ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ R2059_ALL ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,scalar_t__,scalar_t__) ; 
 scalar_t__** r2059_phy_rev1_init ; 

void r2059_upload_inittabs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u16 *table = NULL;
	u16 size, i;

	switch (phy->rev) {
	case 1:
		table = r2059_phy_rev1_init[0];
		size = ARRAY_SIZE(r2059_phy_rev1_init);
		break;
	default:
		B43_WARN_ON(1);
		return;
	}

	for (i = 0; i < size; i++, table += 2)
		b43_radio_write(dev, R2059_ALL | table[0], table[1]);
}