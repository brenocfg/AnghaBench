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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nes_read_1G_phy_reg (struct nes_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nes_write_1G_phy_reg (struct nes_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int nes_init_1g_phy(struct nes_device *nesdev, u8 phy_type, u8 phy_index)
{
	u32 counter = 0;
	u16 phy_data;
	int ret = 0;

	nes_read_1G_phy_reg(nesdev, 1, phy_index, &phy_data);
	nes_write_1G_phy_reg(nesdev, 23, phy_index, 0xb000);

	/* Reset the PHY */
	nes_write_1G_phy_reg(nesdev, 0, phy_index, 0x8000);
	udelay(100);
	counter = 0;
	do {
		nes_read_1G_phy_reg(nesdev, 0, phy_index, &phy_data);
		if (counter++ > 100) {
			ret = -1;
			break;
		}
	} while (phy_data & 0x8000);

	/* Setting no phy loopback */
	phy_data &= 0xbfff;
	phy_data |= 0x1140;
	nes_write_1G_phy_reg(nesdev, 0, phy_index,  phy_data);
	nes_read_1G_phy_reg(nesdev, 0, phy_index, &phy_data);
	nes_read_1G_phy_reg(nesdev, 0x17, phy_index, &phy_data);
	nes_read_1G_phy_reg(nesdev, 0x1e, phy_index, &phy_data);

	/* Setting the interrupt mask */
	nes_read_1G_phy_reg(nesdev, 0x19, phy_index, &phy_data);
	nes_write_1G_phy_reg(nesdev, 0x19, phy_index, 0xffee);
	nes_read_1G_phy_reg(nesdev, 0x19, phy_index, &phy_data);

	/* turning on flow control */
	nes_read_1G_phy_reg(nesdev, 4, phy_index, &phy_data);
	nes_write_1G_phy_reg(nesdev, 4, phy_index, (phy_data & ~(0x03E0)) | 0xc00);
	nes_read_1G_phy_reg(nesdev, 4, phy_index, &phy_data);

	/* Clear Half duplex */
	nes_read_1G_phy_reg(nesdev, 9, phy_index, &phy_data);
	nes_write_1G_phy_reg(nesdev, 9, phy_index, phy_data & ~(0x0100));
	nes_read_1G_phy_reg(nesdev, 9, phy_index, &phy_data);

	nes_read_1G_phy_reg(nesdev, 0, phy_index, &phy_data);
	nes_write_1G_phy_reg(nesdev, 0, phy_index, phy_data | 0x0300);

	return ret;
}