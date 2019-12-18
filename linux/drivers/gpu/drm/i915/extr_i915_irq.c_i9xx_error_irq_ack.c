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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  EMR ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i9xx_error_irq_ack(struct drm_i915_private *dev_priv,
			       u32 *eir, u32 *eir_stuck)
{
	u32 emr;

	*eir = I915_READ(EIR);

	I915_WRITE(EIR, *eir);

	*eir_stuck = I915_READ(EIR);
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
	emr = I915_READ(EMR);
	I915_WRITE(EMR, 0xffffffff);
	I915_WRITE(EMR, emr | *eir_stuck);
}