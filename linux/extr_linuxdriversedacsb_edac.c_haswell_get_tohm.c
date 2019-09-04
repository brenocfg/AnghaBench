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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_vtd; } ;
struct sbridge_pvt {TYPE_1__ info; } ;

/* Variables and functions */
 int GET_BITFIELD (int,int,int) ; 
 int /*<<< orphan*/  HASWELL_TOHM_0 ; 
 int /*<<< orphan*/  HASWELL_TOHM_1 ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u64 haswell_get_tohm(struct sbridge_pvt *pvt)
{
	u64 rc;
	u32 reg;

	pci_read_config_dword(pvt->info.pci_vtd, HASWELL_TOHM_0, &reg);
	rc = GET_BITFIELD(reg, 26, 31);
	pci_read_config_dword(pvt->info.pci_vtd, HASWELL_TOHM_1, &reg);
	rc = ((reg << 6) | rc) << 26;

	return rc | 0x1ffffff;
}