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
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 unsigned short ASC_BIOS_BANK_SIZE ; 
 unsigned short ASC_BIOS_MIN_ADDR ; 
 unsigned short ASC_IS_EISA ; 
 unsigned short ASC_IS_ISAPNP ; 
 unsigned short ASC_IS_PCI ; 
 unsigned short AscGetChipCfgLsw (int /*<<< orphan*/ ) ; 
 unsigned short AscGetEisaChipCfg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short AscGetChipBiosAddress(PortAddr iop_base,
					    unsigned short bus_type)
{
	unsigned short cfg_lsw;
	unsigned short bios_addr;

	/*
	 * The PCI BIOS is re-located by the motherboard BIOS. Because
	 * of this the driver can not determine where a PCI BIOS is
	 * loaded and executes.
	 */
	if (bus_type & ASC_IS_PCI)
		return 0;

	if ((bus_type & ASC_IS_EISA) != 0) {
		cfg_lsw = AscGetEisaChipCfg(iop_base);
		cfg_lsw &= 0x000F;
		bios_addr = ASC_BIOS_MIN_ADDR + cfg_lsw * ASC_BIOS_BANK_SIZE;
		return bios_addr;
	}

	cfg_lsw = AscGetChipCfgLsw(iop_base);

	/*
	 *  ISA PnP uses the top bit as the 32K BIOS flag
	 */
	if (bus_type == ASC_IS_ISAPNP)
		cfg_lsw &= 0x7FFF;
	bios_addr = ASC_BIOS_MIN_ADDR + (cfg_lsw >> 12) * ASC_BIOS_BANK_SIZE;
	return bios_addr;
}