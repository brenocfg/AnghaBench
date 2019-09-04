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
typedef  int /*<<< orphan*/  u64 ;
struct drm_i915_private {int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_terminally_wedged (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i915_wedged_get(void *data, u64 *val)
{
	struct drm_i915_private *dev_priv = data;

	*val = i915_terminally_wedged(&dev_priv->gpu_error);

	return 0;
}