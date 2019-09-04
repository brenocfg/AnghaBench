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
typedef  int u32 ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long MIPS_CMGCRF_BASE ; 
 int MIPS_CONF3_CMGCR ; 
 unsigned long read_c0_cmgcrbase () ; 
 int read_c0_config3 () ; 

phys_addr_t __mips_cm_phys_base(void)
{
	u32 config3 = read_c0_config3();
	unsigned long cmgcr;

	/* Check the CMGCRBase register is implemented */
	if (!(config3 & MIPS_CONF3_CMGCR))
		return 0;

	/* Read the address from CMGCRBase */
	cmgcr = read_c0_cmgcrbase();
	return (cmgcr & MIPS_CMGCRF_BASE) << (36 - 32);
}