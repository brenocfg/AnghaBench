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
struct intel_uncore {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_uncore_posting_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

void gen3_irq_reset(struct intel_uncore *uncore, i915_reg_t imr,
		    i915_reg_t iir, i915_reg_t ier)
{
	intel_uncore_write(uncore, imr, 0xffffffff);
	intel_uncore_posting_read(uncore, imr);

	intel_uncore_write(uncore, ier, 0);

	/* IIR can theoretically queue up two events. Be paranoid. */
	intel_uncore_write(uncore, iir, 0xffffffff);
	intel_uncore_posting_read(uncore, iir);
	intel_uncore_write(uncore, iir, 0xffffffff);
	intel_uncore_posting_read(uncore, iir);
}