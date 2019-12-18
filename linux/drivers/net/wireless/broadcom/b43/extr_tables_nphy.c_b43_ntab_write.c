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
typedef  int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATALO ; 
#define  B43_NTAB_16BIT 130 
#define  B43_NTAB_32BIT 129 
#define  B43_NTAB_8BIT 128 
 int B43_NTAB_TYPEMASK ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  assert_ntab_array_sizes () ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

void b43_ntab_write(struct b43_wldev *dev, u32 offset, u32 value)
{
	u32 type;

	type = offset & B43_NTAB_TYPEMASK;
	offset &= 0xFFFF;

	switch (type) {
	case B43_NTAB_8BIT:
		B43_WARN_ON(value & ~0xFF);
		b43_phy_write(dev, B43_NPHY_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_NPHY_TABLE_DATALO, value);
		break;
	case B43_NTAB_16BIT:
		B43_WARN_ON(value & ~0xFFFF);
		b43_phy_write(dev, B43_NPHY_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_NPHY_TABLE_DATALO, value);
		break;
	case B43_NTAB_32BIT:
		b43_phy_write(dev, B43_NPHY_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_NPHY_TABLE_DATAHI, value >> 16);
		b43_phy_write(dev, B43_NPHY_TABLE_DATALO, value & 0xFFFF);
		break;
	default:
		B43_WARN_ON(1);
	}

	return;

	/* Some compiletime assertions... */
	assert_ntab_array_sizes();
}