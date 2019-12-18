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
struct TYPE_2__ {scalar_t__ spx0; scalar_t__ spx1; } ;
union cvmx_npi_rsl_int_blocks {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NPI_RSL_INT_BLOCKS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  cvm_oct_spi_spx_int (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cvm_oct_spi_rml_interrupt(int cpl, void *dev_id)
{
	irqreturn_t return_status = IRQ_NONE;
	union cvmx_npi_rsl_int_blocks rsl_int_blocks;

	/* Check and see if this interrupt was caused by the GMX block */
	rsl_int_blocks.u64 = cvmx_read_csr(CVMX_NPI_RSL_INT_BLOCKS);
	if (rsl_int_blocks.s.spx1) /* 19 - SPX1_INT_REG & STX1_INT_REG */
		return_status = cvm_oct_spi_spx_int(1);

	if (rsl_int_blocks.s.spx0) /* 18 - SPX0_INT_REG & STX0_INT_REG */
		return_status = cvm_oct_spi_spx_int(0);

	return return_status;
}