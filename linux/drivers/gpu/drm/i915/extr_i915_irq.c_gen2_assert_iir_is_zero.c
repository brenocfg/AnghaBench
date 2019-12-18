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
typedef  scalar_t__ u16 ;
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN2_IIR ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_posting_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gen2_assert_iir_is_zero(struct intel_uncore *uncore)
{
	u16 val = intel_uncore_read16(uncore, GEN2_IIR);

	if (val == 0)
		return;

	WARN(1, "Interrupt register 0x%x is not zero: 0x%08x\n",
	     i915_mmio_reg_offset(GEN2_IIR), val);
	intel_uncore_write16(uncore, GEN2_IIR, 0xffff);
	intel_uncore_posting_read16(uncore, GEN2_IIR);
	intel_uncore_write16(uncore, GEN2_IIR, 0xffff);
	intel_uncore_posting_read16(uncore, GEN2_IIR);
}