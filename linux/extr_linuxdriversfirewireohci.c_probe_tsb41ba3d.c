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
struct fw_ohci {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int PHY_EXTENDED_REGISTERS ; 
 int read_paged_phy_reg (struct fw_ohci*,int,int) ; 
 int read_phy_reg (struct fw_ohci*,int) ; 

__attribute__((used)) static int probe_tsb41ba3d(struct fw_ohci *ohci)
{
	/* TI vendor ID = 0x080028, TSB41BA3D product ID = 0x833005 (sic) */
	static const u8 id[] = { 0x08, 0x00, 0x28, 0x83, 0x30, 0x05, };
	int reg, i;

	reg = read_phy_reg(ohci, 2);
	if (reg < 0)
		return reg;
	if ((reg & PHY_EXTENDED_REGISTERS) != PHY_EXTENDED_REGISTERS)
		return 0;

	for (i = ARRAY_SIZE(id) - 1; i >= 0; i--) {
		reg = read_paged_phy_reg(ohci, 1, i + 10);
		if (reg < 0)
			return reg;
		if (reg != id[i])
			return 0;
	}
	return 1;
}