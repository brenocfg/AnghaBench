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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  test_irq_rings; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */

__attribute__((used)) static int
i915_ring_test_irq_get(void *data, u64 *val)
{
	struct drm_i915_private *dev_priv = data;

	*val = dev_priv->gpu_error.test_irq_rings;

	return 0;
}