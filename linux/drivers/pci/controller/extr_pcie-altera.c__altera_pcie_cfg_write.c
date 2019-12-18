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
struct TYPE_3__ {int (* rp_write_cfg ) (struct altera_pcie*,scalar_t__,int,int,int) ;} ;

/* Variables and functions */
 int DWORD_MASK ; 
 int stub1 (struct altera_pcie*,scalar_t__,int,int,int) ; 
 int tlp_cfg_dword_write (struct altera_pcie*,scalar_t__,unsigned int,int,scalar_t__,int) ; 

__attribute__((used)) static int _altera_pcie_cfg_write(struct altera_pcie *pcie, u8 busno,
				  unsigned int devfn, int where, int size,
				  u32 value)
{
	u32 data32;
	u32 shift = 8 * (where & 3);
	u8 byte_en;

	if (busno == pcie->root_bus_nr && pcie->pcie_data->ops->rp_write_cfg)
		return pcie->pcie_data->ops->rp_write_cfg(pcie, busno,
						     where, size, value);

	switch (size) {
	case 1:
		data32 = (value & 0xff) << shift;
		byte_en = 1 << (where & 3);
		break;
	case 2:
		data32 = (value & 0xffff) << shift;
		byte_en = 3 << (where & 3);
		break;
	default:
		data32 = value;
		byte_en = 0xf;
		break;
	}

	return tlp_cfg_dword_write(pcie, busno, devfn, (where & ~DWORD_MASK),
				   byte_en, data32);
}