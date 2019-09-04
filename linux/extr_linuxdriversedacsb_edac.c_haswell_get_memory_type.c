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
typedef  int /*<<< orphan*/  u32 ;
struct sbridge_pvt {int /*<<< orphan*/  pci_ta; int /*<<< orphan*/  pci_ddrio; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;

/* Variables and functions */
 scalar_t__ GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HASWELL_DDRCRCLKCONTROLS ; 
 int /*<<< orphan*/  MCMTR ; 
 int MEM_DDR3 ; 
 int MEM_DDR4 ; 
 int MEM_RDDR3 ; 
 int MEM_RDDR4 ; 
 int MEM_UNKNOWN ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum mem_type haswell_get_memory_type(struct sbridge_pvt *pvt)
{
	u32 reg;
	bool registered = false;
	enum mem_type mtype = MEM_UNKNOWN;

	if (!pvt->pci_ddrio)
		goto out;

	pci_read_config_dword(pvt->pci_ddrio,
			      HASWELL_DDRCRCLKCONTROLS, &reg);
	/* Is_Rdimm */
	if (GET_BITFIELD(reg, 16, 16))
		registered = true;

	pci_read_config_dword(pvt->pci_ta, MCMTR, &reg);
	if (GET_BITFIELD(reg, 14, 14)) {
		if (registered)
			mtype = MEM_RDDR4;
		else
			mtype = MEM_DDR4;
	} else {
		if (registered)
			mtype = MEM_RDDR3;
		else
			mtype = MEM_DDR3;
	}

out:
	return mtype;
}