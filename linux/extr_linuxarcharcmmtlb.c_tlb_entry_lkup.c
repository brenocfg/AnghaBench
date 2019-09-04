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

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_TLBCOMMAND ; 
 int /*<<< orphan*/  ARC_REG_TLBINDEX ; 
 int /*<<< orphan*/  ARC_REG_TLBPD0 ; 
 unsigned long TLBProbe ; 
 unsigned int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline unsigned int tlb_entry_lkup(unsigned long vaddr_n_asid)
{
	unsigned int idx;

	write_aux_reg(ARC_REG_TLBPD0, vaddr_n_asid);

	write_aux_reg(ARC_REG_TLBCOMMAND, TLBProbe);
	idx = read_aux_reg(ARC_REG_TLBINDEX);

	return idx;
}