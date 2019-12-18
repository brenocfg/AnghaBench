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
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN2_IER ; 
 int /*<<< orphan*/  GEN2_IMR ; 
 int /*<<< orphan*/  gen2_assert_iir_is_zero (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uncore_posting_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gen2_irq_init(struct intel_uncore *uncore,
		   u32 imr_val, u32 ier_val)
{
	gen2_assert_iir_is_zero(uncore);

	intel_uncore_write16(uncore, GEN2_IER, ier_val);
	intel_uncore_write16(uncore, GEN2_IMR, imr_val);
	intel_uncore_posting_read16(uncore, GEN2_IMR);
}