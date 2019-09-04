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
struct TYPE_2__ {unsigned long bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IPI_CALL_FUNC ; 
 unsigned long IPI_MAX ; 
 int IPI_RESCHEDULE ; 
 int /*<<< orphan*/  SIE_SSIE ; 
 int /*<<< orphan*/  csr_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 TYPE_1__* ipi_data ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int /*<<< orphan*/  sip ; 
 size_t smp_processor_id () ; 
 unsigned long xchg (unsigned long*,int /*<<< orphan*/ ) ; 

void riscv_software_interrupt(void)
{
	unsigned long *pending_ipis = &ipi_data[smp_processor_id()].bits;

	/* Clear pending IPI */
	csr_clear(sip, SIE_SSIE);

	while (true) {
		unsigned long ops;

		/* Order bit clearing and data access. */
		mb();

		ops = xchg(pending_ipis, 0);
		if (ops == 0)
			return;

		if (ops & (1 << IPI_RESCHEDULE))
			scheduler_ipi();

		if (ops & (1 << IPI_CALL_FUNC))
			generic_smp_call_function_interrupt();

		BUG_ON((ops >> IPI_MAX) != 0);

		/* Order data access and bit testing. */
		mb();
	}
}