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
typedef  int u16 ;
struct uli526x_board_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_DATA_0 ; 
 int /*<<< orphan*/  PHY_DATA_1 ; 
 int phy_read_1bit (struct uli526x_board_info*) ; 
 int /*<<< orphan*/  phy_write_1bit (struct uli526x_board_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 phy_readby_cr9(struct uli526x_board_info *db, u8 phy_addr, u8 offset)
{
	u16 phy_data;
	int i;

	/* Send 33 synchronization clock to Phy controller */
	for (i = 0; i < 35; i++)
		phy_write_1bit(db, PHY_DATA_1);

	/* Send start command(01) to Phy */
	phy_write_1bit(db, PHY_DATA_0);
	phy_write_1bit(db, PHY_DATA_1);

	/* Send read command(10) to Phy */
	phy_write_1bit(db, PHY_DATA_1);
	phy_write_1bit(db, PHY_DATA_0);

	/* Send Phy address */
	for (i = 0x10; i > 0; i = i >> 1)
		phy_write_1bit(db, phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Send register address */
	for (i = 0x10; i > 0; i = i >> 1)
		phy_write_1bit(db, offset & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Skip transition state */
	phy_read_1bit(db);

	/* read 16bit data */
	for (phy_data = 0, i = 0; i < 16; i++) {
		phy_data <<= 1;
		phy_data |= phy_read_1bit(db);
	}

	return phy_data;
}