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

/* Variables and functions */
 int /*<<< orphan*/  GEN2_IER ; 
 int /*<<< orphan*/  GEN2_IIR ; 
 int /*<<< orphan*/  GEN2_IMR ; 
 int /*<<< orphan*/  intel_uncore_posting_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

void gen2_irq_reset(struct intel_uncore *uncore)
{
	intel_uncore_write16(uncore, GEN2_IMR, 0xffff);
	intel_uncore_posting_read16(uncore, GEN2_IMR);

	intel_uncore_write16(uncore, GEN2_IER, 0);

	/* IIR can theoretically queue up two events. Be paranoid. */
	intel_uncore_write16(uncore, GEN2_IIR, 0xffff);
	intel_uncore_posting_read16(uncore, GEN2_IIR);
	intel_uncore_write16(uncore, GEN2_IIR, 0xffff);
	intel_uncore_posting_read16(uncore, GEN2_IIR);
}