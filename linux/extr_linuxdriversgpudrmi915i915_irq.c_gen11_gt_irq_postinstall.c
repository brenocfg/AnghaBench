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
struct drm_i915_private {int pm_ier; int pm_imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int const) ; 
 int /*<<< orphan*/  GEN11_BCS_RSVD_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_RCS0_RSVD_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_RENDER_COPY_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_VCS0_VCS1_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_VCS2_VCS3_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_VCS_VECS_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_VECS0_VECS1_INTR_MASK ; 
 int GT_CONTEXT_SWITCH_INTERRUPT ; 
 int GT_RENDER_USER_INTERRUPT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void gen11_gt_irq_postinstall(struct drm_i915_private *dev_priv)
{
	const u32 irqs = GT_RENDER_USER_INTERRUPT | GT_CONTEXT_SWITCH_INTERRUPT;

	BUILD_BUG_ON(irqs & 0xffff0000);

	/* Enable RCS, BCS, VCS and VECS class interrupts. */
	I915_WRITE(GEN11_RENDER_COPY_INTR_ENABLE, irqs << 16 | irqs);
	I915_WRITE(GEN11_VCS_VECS_INTR_ENABLE,	  irqs << 16 | irqs);

	/* Unmask irqs on RCS, BCS, VCS and VECS engines. */
	I915_WRITE(GEN11_RCS0_RSVD_INTR_MASK,	~(irqs << 16));
	I915_WRITE(GEN11_BCS_RSVD_INTR_MASK,	~(irqs << 16));
	I915_WRITE(GEN11_VCS0_VCS1_INTR_MASK,	~(irqs | irqs << 16));
	I915_WRITE(GEN11_VCS2_VCS3_INTR_MASK,	~(irqs | irqs << 16));
	I915_WRITE(GEN11_VECS0_VECS1_INTR_MASK,	~(irqs | irqs << 16));

	/*
	 * RPS interrupts will get enabled/disabled on demand when RPS itself
	 * is enabled/disabled.
	 */
	dev_priv->pm_ier = 0x0;
	dev_priv->pm_imr = ~dev_priv->pm_ier;
	I915_WRITE(GEN11_GPM_WGBOXPERF_INTR_ENABLE, 0);
	I915_WRITE(GEN11_GPM_WGBOXPERF_INTR_MASK,  ~0);
}