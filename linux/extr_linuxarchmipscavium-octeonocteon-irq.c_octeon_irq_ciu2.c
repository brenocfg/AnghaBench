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
typedef  int u64 ;

/* Variables and functions */
 int CVMX_CIU2_ACK_PPX_IP2 (unsigned long const) ; 
 int CVMX_CIU2_INTR_CIU_READY ; 
 int CVMX_CIU2_SRC_PPX_IP2_WRKQ (unsigned long const) ; 
 int CVMX_CIU2_SUM_PPX_IP2 (unsigned long const) ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 unsigned long cvmx_get_core_num () ; 
 int cvmx_read_csr (int) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls64 (int) ; 
 int** octeon_irq_ciu_to_irq ; 
 int /*<<< orphan*/  spurious_interrupt () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void octeon_irq_ciu2(void)
{
	int line;
	int bit;
	int irq;
	u64 src_reg, src, sum;
	const unsigned long core_id = cvmx_get_core_num();

	sum = cvmx_read_csr(CVMX_CIU2_SUM_PPX_IP2(core_id)) & 0xfful;

	if (unlikely(!sum))
		goto spurious;

	line = fls64(sum) - 1;
	src_reg = CVMX_CIU2_SRC_PPX_IP2_WRKQ(core_id) + (0x1000 * line);
	src = cvmx_read_csr(src_reg);

	if (unlikely(!src))
		goto spurious;

	bit = fls64(src) - 1;
	irq = octeon_irq_ciu_to_irq[line][bit];
	if (unlikely(!irq))
		goto spurious;

	do_IRQ(irq);
	goto out;

spurious:
	spurious_interrupt();
out:
	/* CN68XX pass 1.x has an errata that accessing the ACK registers
		can stop interrupts from propagating */
	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		cvmx_read_csr(CVMX_CIU2_INTR_CIU_READY);
	else
		cvmx_read_csr(CVMX_CIU2_ACK_PPX_IP2(core_id));
	return;
}