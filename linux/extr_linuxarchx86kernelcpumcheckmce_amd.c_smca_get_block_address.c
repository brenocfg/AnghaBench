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

/* Variables and functions */
 int MASK_BLKPTR_LO ; 
 int MCI_CONFIG_MCAX ; 
 int MSR_AMD64_SMCA_MCx_CONFIG (unsigned int) ; 
 int MSR_AMD64_SMCA_MCx_MISC (unsigned int) ; 
 int MSR_AMD64_SMCA_MCx_MISCy (unsigned int,unsigned int) ; 
 scalar_t__ SMCA_RESERVED ; 
 scalar_t__ rdmsr_safe (int,int*,int*) ; 
 int** smca_bank_addrs ; 
 scalar_t__ smca_get_bank_type (unsigned int) ; 

__attribute__((used)) static u32 smca_get_block_address(unsigned int bank, unsigned int block)
{
	u32 low, high;
	u32 addr = 0;

	if (smca_get_bank_type(bank) == SMCA_RESERVED)
		return addr;

	if (!block)
		return MSR_AMD64_SMCA_MCx_MISC(bank);

	/* Check our cache first: */
	if (smca_bank_addrs[bank][block] != -1)
		return smca_bank_addrs[bank][block];

	/*
	 * For SMCA enabled processors, BLKPTR field of the first MISC register
	 * (MCx_MISC0) indicates presence of additional MISC regs set (MISC1-4).
	 */
	if (rdmsr_safe(MSR_AMD64_SMCA_MCx_CONFIG(bank), &low, &high))
		goto out;

	if (!(low & MCI_CONFIG_MCAX))
		goto out;

	if (!rdmsr_safe(MSR_AMD64_SMCA_MCx_MISC(bank), &low, &high) &&
	    (low & MASK_BLKPTR_LO))
		addr = MSR_AMD64_SMCA_MCx_MISCy(bank, block - 1);

out:
	smca_bank_addrs[bank][block] = addr;
	return addr;
}