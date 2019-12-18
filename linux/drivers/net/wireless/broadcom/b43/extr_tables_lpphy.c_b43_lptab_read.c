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
 int /*<<< orphan*/  B43_LPPHY_TABLEDATAHI ; 
 int /*<<< orphan*/  B43_LPPHY_TABLEDATALO ; 
 int /*<<< orphan*/  B43_LPPHY_TABLE_ADDR ; 
#define  B43_LPTAB_16BIT 130 
#define  B43_LPTAB_32BIT 129 
#define  B43_LPTAB_8BIT 128 
 int B43_LPTAB_TYPEMASK ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

u32 b43_lptab_read(struct b43_wldev *dev, u32 offset)
{
	u32 type, value;

	type = offset & B43_LPTAB_TYPEMASK;
	offset &= ~B43_LPTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	switch (type) {
	case B43_LPTAB_8BIT:
		b43_phy_write(dev, B43_LPPHY_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_LPPHY_TABLEDATALO) & 0xFF;
		break;
	case B43_LPTAB_16BIT:
		b43_phy_write(dev, B43_LPPHY_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_LPPHY_TABLEDATALO);
		break;
	case B43_LPTAB_32BIT:
		b43_phy_write(dev, B43_LPPHY_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_LPPHY_TABLEDATAHI);
		value <<= 16;
		value |= b43_phy_read(dev, B43_LPPHY_TABLEDATALO);
		break;
	default:
		B43_WARN_ON(1);
		value = 0;
	}

	return value;
}