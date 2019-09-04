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
typedef  int /*<<< orphan*/  u64 ;
struct thunderx_lmc {int node; int dimm_lsb; int rank_lsb; int row_lsb; int col_hi_lsb; int bank_lsb; int xbits; int bank_width; scalar_t__ l2c_alias; TYPE_1__* pdev; scalar_t__ xor_bank; } ;
typedef  int phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int LMC_FADR_FBANK (int /*<<< orphan*/ ) ; 
 int LMC_FADR_FBUNK (int /*<<< orphan*/ ) ; 
 int LMC_FADR_FCOL (int /*<<< orphan*/ ) ; 
 int LMC_FADR_FDIMM (int /*<<< orphan*/ ) ; 
 int LMC_FADR_FROW (int /*<<< orphan*/ ) ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int get_bits (int,int,int) ; 

__attribute__((used)) static phys_addr_t thunderx_faddr_to_phys(u64 faddr, struct thunderx_lmc *lmc)
{
	phys_addr_t addr = 0;
	int bank, xbits;

	addr |= lmc->node << 40;
	addr |= LMC_FADR_FDIMM(faddr) << lmc->dimm_lsb;
	addr |= LMC_FADR_FBUNK(faddr) << lmc->rank_lsb;
	addr |= LMC_FADR_FROW(faddr) << lmc->row_lsb;
	addr |= (LMC_FADR_FCOL(faddr) >> 4) << lmc->col_hi_lsb;

	bank = LMC_FADR_FBANK(faddr) << lmc->bank_lsb;

	if (lmc->xor_bank)
		bank ^= get_bits(addr, 12 + lmc->xbits, lmc->bank_width);

	addr |= bank << lmc->bank_lsb;

	xbits = PCI_FUNC(lmc->pdev->devfn);

	if (lmc->l2c_alias)
		xbits ^= get_bits(addr, 20, lmc->xbits) ^
			 get_bits(addr, 12, lmc->xbits);

	addr |= xbits << 7;

	return addr;
}