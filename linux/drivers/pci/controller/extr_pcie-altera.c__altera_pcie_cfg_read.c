#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct altera_pcie {scalar_t__ root_bus_nr; TYPE_2__* pcie_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* rp_read_cfg ) (struct altera_pcie*,int,int,int*) ;} ;

/* Variables and functions */
 int DWORD_MASK ; 
 int PCIBIOS_SUCCESSFUL ; 
 int stub1 (struct altera_pcie*,int,int,int*) ; 
 int tlp_cfg_dword_read (struct altera_pcie*,scalar_t__,unsigned int,int,scalar_t__,int*) ; 

__attribute__((used)) static int _altera_pcie_cfg_read(struct altera_pcie *pcie, u8 busno,
				 unsigned int devfn, int where, int size,
				 u32 *value)
{
	int ret;
	u32 data;
	u8 byte_en;

	if (busno == pcie->root_bus_nr && pcie->pcie_data->ops->rp_read_cfg)
		return pcie->pcie_data->ops->rp_read_cfg(pcie, where,
							 size, value);

	switch (size) {
	case 1:
		byte_en = 1 << (where & 3);
		break;
	case 2:
		byte_en = 3 << (where & 3);
		break;
	default:
		byte_en = 0xf;
		break;
	}

	ret = tlp_cfg_dword_read(pcie, busno, devfn,
				 (where & ~DWORD_MASK), byte_en, &data);
	if (ret != PCIBIOS_SUCCESSFUL)
		return ret;

	switch (size) {
	case 1:
		*value = (data >> (8 * (where & 0x3))) & 0xff;
		break;
	case 2:
		*value = (data >> (8 * (where & 0x2))) & 0xffff;
		break;
	default:
		*value = data;
		break;
	}

	return PCIBIOS_SUCCESSFUL;
}