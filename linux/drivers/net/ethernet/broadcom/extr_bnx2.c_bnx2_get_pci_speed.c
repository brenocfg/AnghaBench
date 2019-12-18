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
struct bnx2 {int bus_speed_mhz; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_FLAG_PCIX ; 
 int /*<<< orphan*/  BNX2_FLAG_PCI_32BIT ; 
 int /*<<< orphan*/  BNX2_PCICFG_MISC_STATUS ; 
 int BNX2_PCICFG_MISC_STATUS_32BIT_DET ; 
 int BNX2_PCICFG_MISC_STATUS_M66EN ; 
 int BNX2_PCICFG_MISC_STATUS_PCIX_DET ; 
 int /*<<< orphan*/  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS ; 
 int BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET ; 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_133MHZ 136 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_32MHZ 135 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_38MHZ 134 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_48MHZ 133 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_55MHZ 132 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_66MHZ 131 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_80MHZ 130 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_95MHZ 129 
#define  BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_LOW 128 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_get_pci_speed(struct bnx2 *bp)
{
	u32 reg;

	reg = BNX2_RD(bp, BNX2_PCICFG_MISC_STATUS);
	if (reg & BNX2_PCICFG_MISC_STATUS_PCIX_DET) {
		u32 clkreg;

		bp->flags |= BNX2_FLAG_PCIX;

		clkreg = BNX2_RD(bp, BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS);

		clkreg &= BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET;
		switch (clkreg) {
		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_133MHZ:
			bp->bus_speed_mhz = 133;
			break;

		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_95MHZ:
			bp->bus_speed_mhz = 100;
			break;

		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_66MHZ:
		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_80MHZ:
			bp->bus_speed_mhz = 66;
			break;

		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_48MHZ:
		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_55MHZ:
			bp->bus_speed_mhz = 50;
			break;

		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_LOW:
		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_32MHZ:
		case BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_38MHZ:
			bp->bus_speed_mhz = 33;
			break;
		}
	}
	else {
		if (reg & BNX2_PCICFG_MISC_STATUS_M66EN)
			bp->bus_speed_mhz = 66;
		else
			bp->bus_speed_mhz = 33;
	}

	if (reg & BNX2_PCICFG_MISC_STATUS_32BIT_DET)
		bp->flags |= BNX2_FLAG_PCI_32BIT;

}