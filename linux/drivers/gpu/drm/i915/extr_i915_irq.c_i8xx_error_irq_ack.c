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
typedef  int u16 ;
struct intel_uncore {int dummy; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  EMR ; 
 int intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i8xx_error_irq_ack(struct drm_i915_private *i915,
			       u16 *eir, u16 *eir_stuck)
{
	struct intel_uncore *uncore = &i915->uncore;
	u16 emr;

	*eir = intel_uncore_read16(uncore, EIR);

	if (*eir)
		intel_uncore_write16(uncore, EIR, *eir);

	*eir_stuck = intel_uncore_read16(uncore, EIR);
	if (*eir_stuck == 0)
		return;

	/*
	 * Toggle all EMR bits to make sure we get an edge
	 * in the ISR master error bit if we don't clear
	 * all the EIR bits. Otherwise the edge triggered
	 * IIR on i965/g4x wouldn't notice that an interrupt
	 * is still pending. Also some EIR bits can't be
	 * cleared except by handling the underlying error
	 * (or by a GPU reset) so we mask any bit that
	 * remains set.
	 */
	emr = intel_uncore_read16(uncore, EMR);
	intel_uncore_write16(uncore, EMR, 0xffff);
	intel_uncore_write16(uncore, EMR, emr | *eir_stuck);
}