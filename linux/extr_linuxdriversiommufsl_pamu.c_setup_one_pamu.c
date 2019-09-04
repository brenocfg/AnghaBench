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
struct pamu_mmap_regs {int /*<<< orphan*/  olal; int /*<<< orphan*/  olah; int /*<<< orphan*/  obal; int /*<<< orphan*/  obah; int /*<<< orphan*/  splal; int /*<<< orphan*/  splah; int /*<<< orphan*/  spbal; int /*<<< orphan*/  spbah; int /*<<< orphan*/  pplal; int /*<<< orphan*/  pplah; int /*<<< orphan*/  ppbal; int /*<<< orphan*/  ppbah; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ OMT_SIZE ; 
 scalar_t__ PAACT_SIZE ; 
 int PAMU_ACCESS_VIOLATION_ENABLE ; 
 scalar_t__ PAMU_MMAP_REGS_BASE ; 
 scalar_t__ PAMU_PC ; 
 int PAMU_PC_OCE ; 
 int PAMU_PC_PE ; 
 int PAMU_PC_PPCC ; 
 int PAMU_PC_SPCC ; 
 scalar_t__ PAMU_PICS ; 
 scalar_t__ SPAACT_SIZE ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int setup_one_pamu(unsigned long pamu_reg_base, unsigned long pamu_reg_size,
			  phys_addr_t ppaact_phys, phys_addr_t spaact_phys,
			  phys_addr_t omt_phys)
{
	u32 *pc;
	struct pamu_mmap_regs *pamu_regs;

	pc = (u32 *) (pamu_reg_base + PAMU_PC);
	pamu_regs = (struct pamu_mmap_regs *)
		(pamu_reg_base + PAMU_MMAP_REGS_BASE);

	/* set up pointers to corenet control blocks */

	out_be32(&pamu_regs->ppbah, upper_32_bits(ppaact_phys));
	out_be32(&pamu_regs->ppbal, lower_32_bits(ppaact_phys));
	ppaact_phys = ppaact_phys + PAACT_SIZE;
	out_be32(&pamu_regs->pplah, upper_32_bits(ppaact_phys));
	out_be32(&pamu_regs->pplal, lower_32_bits(ppaact_phys));

	out_be32(&pamu_regs->spbah, upper_32_bits(spaact_phys));
	out_be32(&pamu_regs->spbal, lower_32_bits(spaact_phys));
	spaact_phys = spaact_phys + SPAACT_SIZE;
	out_be32(&pamu_regs->splah, upper_32_bits(spaact_phys));
	out_be32(&pamu_regs->splal, lower_32_bits(spaact_phys));

	out_be32(&pamu_regs->obah, upper_32_bits(omt_phys));
	out_be32(&pamu_regs->obal, lower_32_bits(omt_phys));
	omt_phys = omt_phys + OMT_SIZE;
	out_be32(&pamu_regs->olah, upper_32_bits(omt_phys));
	out_be32(&pamu_regs->olal, lower_32_bits(omt_phys));

	/*
	 * set PAMU enable bit,
	 * allow ppaact & omt to be cached
	 * & enable PAMU access violation interrupts.
	 */

	out_be32((u32 *)(pamu_reg_base + PAMU_PICS),
		 PAMU_ACCESS_VIOLATION_ENABLE);
	out_be32(pc, PAMU_PC_PE | PAMU_PC_OCE | PAMU_PC_SPCC | PAMU_PC_PPCC);
	return 0;
}