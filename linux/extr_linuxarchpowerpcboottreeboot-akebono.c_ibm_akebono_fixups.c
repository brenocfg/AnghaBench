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

/* Variables and functions */
 int /*<<< orphan*/  CCTL0_MCO2 ; 
 int /*<<< orphan*/  CCTL0_MCO4 ; 
 int /*<<< orphan*/  dt_fixup_memory (int,int /*<<< orphan*/ ) ; 
 void* finddevice (char*) ; 
 int /*<<< orphan*/  ibm_akebono_memsize ; 
 scalar_t__ mac_addr ; 
 int mfdcrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdcrx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setprop (void*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ibm_akebono_fixups(void)
{
	void *emac;
	u32 reg;

	dt_fixup_memory(0x0ULL,  ibm_akebono_memsize);

	/* Fixup the SD timeout frequency */
	mtdcrx(CCTL0_MCO4, 0x1);

	/* Disable SD high-speed mode (which seems to be broken) */
	reg = mfdcrx(CCTL0_MCO2) & ~0x2;
	mtdcrx(CCTL0_MCO2, reg);

	/* Set the MAC address */
	emac = finddevice("/plb/opb/ethernet");
	if (emac > 0) {
		if (mac_addr)
			setprop(emac, "local-mac-address",
				((u8 *) &mac_addr) + 2 , 6);
	}
}