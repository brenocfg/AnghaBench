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
typedef  scalar_t__ u32 ;
struct altera_pcie {scalar_t__ root_bus_nr; TYPE_2__* pcie_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* tlp_read_pkt ) (struct altera_pcie*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* tlp_write_pkt ) (struct altera_pcie*,scalar_t__*,scalar_t__,int) ;} ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_PRIMARY_BUS ; 
 int TLP_HDR_SIZE ; 
 int /*<<< orphan*/  get_tlp_header (struct altera_pcie*,scalar_t__,scalar_t__,int,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (struct altera_pcie*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (struct altera_pcie*,scalar_t__*,scalar_t__,int) ; 
 int stub3 (struct altera_pcie*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tlp_cfg_dword_write(struct altera_pcie *pcie, u8 bus, u32 devfn,
			       int where, u8 byte_en, u32 value)
{
	u32 headers[TLP_HDR_SIZE];
	int ret;

	get_tlp_header(pcie, bus, devfn, where, byte_en, false,
		       headers);

	/* check alignment to Qword */
	if ((where & 0x7) == 0)
		pcie->pcie_data->ops->tlp_write_pkt(pcie, headers,
						    value, true);
	else
		pcie->pcie_data->ops->tlp_write_pkt(pcie, headers,
						    value, false);

	ret = pcie->pcie_data->ops->tlp_read_pkt(pcie, NULL);
	if (ret != PCIBIOS_SUCCESSFUL)
		return ret;

	/*
	 * Monitor changes to PCI_PRIMARY_BUS register on root port
	 * and update local copy of root bus number accordingly.
	 */
	if ((bus == pcie->root_bus_nr) && (where == PCI_PRIMARY_BUS))
		pcie->root_bus_nr = (u8)(value);

	return PCIBIOS_SUCCESSFUL;
}