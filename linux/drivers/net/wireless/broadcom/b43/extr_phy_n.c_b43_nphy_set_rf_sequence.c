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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_n {scalar_t__ hang_avoid; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB8 (int,int) ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_ntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void b43_nphy_set_rf_sequence(struct b43_wldev *dev, u8 cmd,
					u8 *events, u8 *delays, u8 length)
{
	struct b43_phy_n *nphy = dev->phy.n;
	u8 i;
	u8 end = (dev->phy.rev >= 3) ? 0x1F : 0x0F;
	u16 offset1 = cmd << 4;
	u16 offset2 = offset1 + 0x80;

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_ntab_write_bulk(dev, B43_NTAB8(7, offset1), length, events);
	b43_ntab_write_bulk(dev, B43_NTAB8(7, offset2), length, delays);

	for (i = length; i < 16; i++) {
		b43_ntab_write(dev, B43_NTAB8(7, offset1 + i), end);
		b43_ntab_write(dev, B43_NTAB8(7, offset2 + i), 1);
	}

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, false);
}