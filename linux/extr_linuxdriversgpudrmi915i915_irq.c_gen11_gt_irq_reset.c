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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_BCS_RSVD_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_RCS0_RSVD_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_RENDER_COPY_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_VCS0_VCS1_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_VCS2_VCS3_INTR_MASK ; 
 int /*<<< orphan*/  GEN11_VCS_VECS_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_VECS0_VECS1_INTR_MASK ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen11_gt_irq_reset(struct drm_i915_private *dev_priv)
{
	/* Disable RCS, BCS, VCS and VECS class engines. */
	I915_WRITE(GEN11_RENDER_COPY_INTR_ENABLE, 0);
	I915_WRITE(GEN11_VCS_VECS_INTR_ENABLE,	  0);

	/* Restore masks irqs on RCS, BCS, VCS and VECS engines. */
	I915_WRITE(GEN11_RCS0_RSVD_INTR_MASK,	~0);
	I915_WRITE(GEN11_BCS_RSVD_INTR_MASK,	~0);
	I915_WRITE(GEN11_VCS0_VCS1_INTR_MASK,	~0);
	I915_WRITE(GEN11_VCS2_VCS3_INTR_MASK,	~0);
	I915_WRITE(GEN11_VECS0_VECS1_INTR_MASK,	~0);

	I915_WRITE(GEN11_GPM_WGBOXPERF_INTR_ENABLE, 0);
	I915_WRITE(GEN11_GPM_WGBOXPERF_INTR_MASK,  ~0);
}