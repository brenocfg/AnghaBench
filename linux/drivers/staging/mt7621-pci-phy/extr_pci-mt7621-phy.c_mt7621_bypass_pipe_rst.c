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
struct mt7621_pci_phy_instance {int index; } ;
struct mt7621_pci_phy {int dummy; } ;

/* Variables and functions */
 int RG_P0_TO_P1_WIDTH ; 
 int RG_PE1_PIPE_CMD_FRC ; 
 int RG_PE1_PIPE_REG ; 
 int RG_PE1_PIPE_RST ; 
 int phy_read (struct mt7621_pci_phy*,int) ; 
 int /*<<< orphan*/  phy_write (struct mt7621_pci_phy*,int,int) ; 

__attribute__((used)) static void mt7621_bypass_pipe_rst(struct mt7621_pci_phy *phy,
				   struct mt7621_pci_phy_instance *instance)
{
	u32 offset = (instance->index != 1) ?
		RG_PE1_PIPE_REG : RG_PE1_PIPE_REG + RG_P0_TO_P1_WIDTH;
	u32 reg;

	reg = phy_read(phy, offset);
	reg &= ~(RG_PE1_PIPE_RST | RG_PE1_PIPE_CMD_FRC);
	reg |= (RG_PE1_PIPE_RST | RG_PE1_PIPE_CMD_FRC);
	phy_write(phy, reg, offset);
}