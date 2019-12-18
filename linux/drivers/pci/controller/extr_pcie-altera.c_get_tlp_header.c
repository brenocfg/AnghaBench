#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct altera_pcie {scalar_t__ root_bus_nr; TYPE_1__* pcie_data; } ;
struct TYPE_2__ {scalar_t__ cfgrd0; scalar_t__ cfgwr0; scalar_t__ cfgrd1; scalar_t__ cfgwr1; scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ALTERA_PCIE_V1 ; 
 scalar_t__ S10_RP_SECONDARY (struct altera_pcie*) ; 
 int /*<<< orphan*/  TLP_CFG_DW0 (struct altera_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  TLP_CFG_DW1 (struct altera_pcie*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TLP_CFG_DW2 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TLP_READ_TAG ; 
 scalar_t__ TLP_WRITE_TAG ; 

__attribute__((used)) static void get_tlp_header(struct altera_pcie *pcie, u8 bus, u32 devfn,
			   int where, u8 byte_en, bool read, u32 *headers)
{
	u8 cfg;
	u8 cfg0 = read ? pcie->pcie_data->cfgrd0 : pcie->pcie_data->cfgwr0;
	u8 cfg1 = read ? pcie->pcie_data->cfgrd1 : pcie->pcie_data->cfgwr1;
	u8 tag = read ? TLP_READ_TAG : TLP_WRITE_TAG;

	if (pcie->pcie_data->version == ALTERA_PCIE_V1)
		cfg = (bus == pcie->root_bus_nr) ? cfg0 : cfg1;
	else
		cfg = (bus > S10_RP_SECONDARY(pcie)) ? cfg0 : cfg1;

	headers[0] = TLP_CFG_DW0(pcie, cfg);
	headers[1] = TLP_CFG_DW1(pcie, tag, byte_en);
	headers[2] = TLP_CFG_DW2(bus, devfn, where);
}