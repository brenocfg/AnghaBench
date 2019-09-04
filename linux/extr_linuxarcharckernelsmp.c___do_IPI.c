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
#define  IPI_CALL_FUNC 130 
#define  IPI_CPU_STOP 129 
#define  IPI_RESCHEDULE 128 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  ipi_cpu_stop () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 

__attribute__((used)) static inline int __do_IPI(unsigned long msg)
{
	int rc = 0;

	switch (msg) {
	case IPI_RESCHEDULE:
		scheduler_ipi();
		break;

	case IPI_CALL_FUNC:
		generic_smp_call_function_interrupt();
		break;

	case IPI_CPU_STOP:
		ipi_cpu_stop();
		break;

	default:
		rc = 1;
	}

	return rc;
}