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
 unsigned int XICS_IRQ_SPURIOUS ; 
 int /*<<< orphan*/  force_external_irq_replay () ; 
 unsigned int icp_opal_get_xirr () ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (unsigned int) ; 
 scalar_t__ opal_int_eoi (unsigned int) ; 
 int /*<<< orphan*/  xics_host ; 
 int /*<<< orphan*/  xics_mask_unknown_vec (unsigned int) ; 
 int /*<<< orphan*/  xics_push_cppr (unsigned int) ; 

__attribute__((used)) static unsigned int icp_opal_get_irq(void)
{
	unsigned int xirr;
	unsigned int vec;
	unsigned int irq;

	xirr = icp_opal_get_xirr();
	vec = xirr & 0x00ffffff;
	if (vec == XICS_IRQ_SPURIOUS)
		return 0;

	irq = irq_find_mapping(xics_host, vec);
	if (likely(irq)) {
		xics_push_cppr(vec);
		return irq;
	}

	/* We don't have a linux mapping, so have rtas mask it. */
	xics_mask_unknown_vec(vec);

	/* We might learn about it later, so EOI it */
	if (opal_int_eoi(xirr) > 0)
		force_external_irq_replay();

	return 0;
}