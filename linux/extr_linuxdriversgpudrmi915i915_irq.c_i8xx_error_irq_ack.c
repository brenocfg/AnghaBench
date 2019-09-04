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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  EMR ; 
 int I915_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i8xx_error_irq_ack(struct drm_i915_private *dev_priv,
			       u16 *eir, u16 *eir_stuck)
{
	u16 emr;

	*eir = I915_READ16(EIR);

	if (*eir)
		I915_WRITE16(EIR, *eir);

	*eir_stuck = I915_READ16(EIR);
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
	emr = I915_READ16(EMR);
	I915_WRITE16(EMR, 0xffff);
	I915_WRITE16(EMR, emr | *eir_stuck);
}