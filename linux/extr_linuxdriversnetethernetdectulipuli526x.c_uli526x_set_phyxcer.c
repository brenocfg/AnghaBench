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
struct uli_phy_ops {int (* read ) (struct uli526x_board_info*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* write ) (struct uli526x_board_info*,int /*<<< orphan*/ ,int,int) ;} ;
struct uli526x_board_info {int media_mode; int PHY_reg4; int /*<<< orphan*/  phy_addr; struct uli_phy_ops phy; } ;

/* Variables and functions */
#define  ULI526X_100MFD 131 
#define  ULI526X_100MHF 130 
#define  ULI526X_10MFD 129 
#define  ULI526X_10MHF 128 
 int ULI526X_AUTO ; 
 int stub1 (struct uli526x_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct uli526x_board_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (struct uli526x_board_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void uli526x_set_phyxcer(struct uli526x_board_info *db)
{
	struct uli_phy_ops *phy = &db->phy;
	u16 phy_reg;

	/* Phyxcer capability setting */
	phy_reg = phy->read(db, db->phy_addr, 4) & ~0x01e0;

	if (db->media_mode & ULI526X_AUTO) {
		/* AUTO Mode */
		phy_reg |= db->PHY_reg4;
	} else {
		/* Force Mode */
		switch(db->media_mode) {
		case ULI526X_10MHF: phy_reg |= 0x20; break;
		case ULI526X_10MFD: phy_reg |= 0x40; break;
		case ULI526X_100MHF: phy_reg |= 0x80; break;
		case ULI526X_100MFD: phy_reg |= 0x100; break;
		}

	}

  	/* Write new capability to Phyxcer Reg4 */
	if ( !(phy_reg & 0x01e0)) {
		phy_reg|=db->PHY_reg4;
		db->media_mode|=ULI526X_AUTO;
	}
	phy->write(db, db->phy_addr, 4, phy_reg);

 	/* Restart Auto-Negotiation */
	phy->write(db, db->phy_addr, 0, 0x1200);
	udelay(50);
}