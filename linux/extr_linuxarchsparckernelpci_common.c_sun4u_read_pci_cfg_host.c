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
typedef  int u32 ;
typedef  int u16 ;
struct pci_pbm_info {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  pci_config_read16 (int*,int*) ; 
 int /*<<< orphan*/  pci_config_read8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* sun4u_config_mkaddr (struct pci_pbm_info*,unsigned char,unsigned int,int) ; 

__attribute__((used)) static int sun4u_read_pci_cfg_host(struct pci_pbm_info *pbm,
				   unsigned char bus, unsigned int devfn,
				   int where, int size, u32 *value)
{
	u32 tmp32, *addr;
	u16 tmp16;
	u8 tmp8;

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	if (!addr)
		return PCIBIOS_SUCCESSFUL;

	switch (size) {
	case 1:
		if (where < 8) {
			unsigned long align = (unsigned long) addr;

			align &= ~1;
			pci_config_read16((u16 *)align, &tmp16);
			if (where & 1)
				*value = tmp16 >> 8;
			else
				*value = tmp16 & 0xff;
		} else {
			pci_config_read8((u8 *)addr, &tmp8);
			*value = (u32) tmp8;
		}
		break;

	case 2:
		if (where < 8) {
			pci_config_read16((u16 *)addr, &tmp16);
			*value = (u32) tmp16;
		} else {
			pci_config_read8((u8 *)addr, &tmp8);
			*value = (u32) tmp8;
			pci_config_read8(((u8 *)addr) + 1, &tmp8);
			*value |= ((u32) tmp8) << 8;
		}
		break;

	case 4:
		tmp32 = 0xffffffff;
		sun4u_read_pci_cfg_host(pbm, bus, devfn,
					where, 2, &tmp32);
		*value = tmp32;

		tmp32 = 0xffffffff;
		sun4u_read_pci_cfg_host(pbm, bus, devfn,
					where + 2, 2, &tmp32);
		*value |= tmp32 << 16;
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}