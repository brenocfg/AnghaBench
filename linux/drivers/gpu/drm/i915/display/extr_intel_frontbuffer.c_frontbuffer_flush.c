#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int busy_bits; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ fb_tracking; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int /*<<< orphan*/  intel_edp_drrs_flush (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  intel_fbc_flush (struct drm_i915_private*,unsigned int,int) ; 
 int /*<<< orphan*/  intel_psr_flush (struct drm_i915_private*,unsigned int,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void frontbuffer_flush(struct drm_i915_private *i915,
			      unsigned int frontbuffer_bits,
			      enum fb_op_origin origin)
{
	/* Delay flushing when rings are still busy.*/
	spin_lock(&i915->fb_tracking.lock);
	frontbuffer_bits &= ~i915->fb_tracking.busy_bits;
	spin_unlock(&i915->fb_tracking.lock);

	if (!frontbuffer_bits)
		return;

	might_sleep();
	intel_edp_drrs_flush(i915, frontbuffer_bits);
	intel_psr_flush(i915, frontbuffer_bits, origin);
	intel_fbc_flush(i915, frontbuffer_bits, origin);
}