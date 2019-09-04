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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int reset_all_global_seqno (struct drm_i915_private*,scalar_t__) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_gem_set_global_seqno(struct drm_device *dev, u32 seqno)
{
	struct drm_i915_private *i915 = to_i915(dev);

	lockdep_assert_held(&i915->drm.struct_mutex);

	if (seqno == 0)
		return -EINVAL;

	/* HWS page needs to be set less than what we will inject to ring */
	return reset_all_global_seqno(i915, seqno - 1);
}