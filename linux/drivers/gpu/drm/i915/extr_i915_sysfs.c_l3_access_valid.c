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
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EPERM ; 
 int GEN7_L3LOG_SIZE ; 
 int /*<<< orphan*/  HAS_L3_DPF (struct drm_i915_private*) ; 

__attribute__((used)) static int l3_access_valid(struct drm_i915_private *dev_priv, loff_t offset)
{
	if (!HAS_L3_DPF(dev_priv))
		return -EPERM;

	if (offset % 4 != 0)
		return -EINVAL;

	if (offset >= GEN7_L3LOG_SIZE)
		return -ENXIO;

	return 0;
}