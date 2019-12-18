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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
#define  B43_LCNTAB_16BIT 130 
#define  B43_LCNTAB_32BIT 129 
#define  B43_LCNTAB_8BIT 128 
 int B43_LCNTAB_TYPEMASK ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_DATALO ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

void b43_lcntab_read_bulk(struct b43_wldev *dev, u32 offset,
			  unsigned int nr_elements, void *_data)
{
	u32 type;
	u8 *data = _data;
	unsigned int i;

	type = offset & B43_LCNTAB_TYPEMASK;
	offset &= ~B43_LCNTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	b43_phy_write(dev, B43_PHY_LCN_TABLE_ADDR, offset);

	for (i = 0; i < nr_elements; i++) {
		switch (type) {
		case B43_LCNTAB_8BIT:
			*data = b43_phy_read(dev,
					     B43_PHY_LCN_TABLE_DATALO) & 0xFF;
			data++;
			break;
		case B43_LCNTAB_16BIT:
			*((u16 *)data) = b43_phy_read(dev,
						      B43_PHY_LCN_TABLE_DATALO);
			data += 2;
			break;
		case B43_LCNTAB_32BIT:
			*((u32 *)data) = b43_phy_read(dev,
						B43_PHY_LCN_TABLE_DATALO);
			*((u32 *)data) |= (b43_phy_read(dev,
					   B43_PHY_LCN_TABLE_DATAHI) << 16);
			data += 4;
			break;
		default:
			B43_WARN_ON(1);
		}
	}
}