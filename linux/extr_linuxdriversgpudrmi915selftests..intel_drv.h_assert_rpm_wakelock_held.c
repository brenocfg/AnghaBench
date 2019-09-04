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
struct TYPE_2__ {int /*<<< orphan*/  wakeref_count; } ;
struct drm_i915_private {TYPE_1__ runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  assert_rpm_device_not_suspended (struct drm_i915_private*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
assert_rpm_wakelock_held(struct drm_i915_private *dev_priv)
{
	assert_rpm_device_not_suspended(dev_priv);
	WARN_ONCE(!atomic_read(&dev_priv->runtime_pm.wakeref_count),
		  "RPM wakelock ref not held during HW access");
}