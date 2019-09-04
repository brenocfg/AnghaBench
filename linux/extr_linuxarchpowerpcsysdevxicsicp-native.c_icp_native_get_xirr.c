#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  word; } ;
struct TYPE_4__ {TYPE_1__ xirr; } ;

/* Variables and functions */
 TYPE_2__** icp_native_regs ; 
 unsigned int in_be32 (int /*<<< orphan*/ *) ; 
 unsigned int kvmppc_get_xics_latch () ; 
 int smp_processor_id () ; 

__attribute__((used)) static inline unsigned int icp_native_get_xirr(void)
{
	int cpu = smp_processor_id();
	unsigned int xirr;

	/* Handled an interrupt latched by KVM */
	xirr = kvmppc_get_xics_latch();
	if (xirr)
		return xirr;

	return in_be32(&icp_native_regs[cpu]->xirr.word);
}